#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#define CORREL_THRESHOLD 0.30

struct correlTableType{
		int geneNum;
		char name[50];
		float maxCorrel;
		int correlatingGeneNum;
};

void removeGene(struct correlTableType *correlTable, int geneNum, int totalNumOfGenes, int *genesLeft, FILE *out);


int main(int argc, char* argv[]){
	FILE *in_crossCorrelation, *in_geneNameTable, *out;
	int numOfGenes;
	int i,j;
	float correl, correl_max;
	int maxCorrel_gene_num;
	int genesLeft;
		
	struct correlTableType *correlTable;
	
	
	
	// Load in gene names
	in_geneNameTable=fopen("cross_correlation_SRG_gene_name_table.txt","r");
	if(in_geneNameTable==NULL){
		printf("[ERROR] Could not open input file cross_correlation_SRG_gene_name_table.txt. Terminating.\n");
		exit(1);
	}
	numOfGenes=0;
	while(fscanf(in_geneNameTable,"%*s\t%*i")!=EOF){
		numOfGenes++;
	}
	printf("[INFO] Found %i genes in the table\n", numOfGenes);
	
	correlTable=malloc(sizeof(struct correlTableType)*numOfGenes);
	if(correlTable==NULL){
		printf("[ERROR] Could not allocate memory for correlTable. Terminating.\n");
		fclose(in_geneNameTable);
		fclose(in_crossCorrelation);
		exit(1);
	}
	rewind(in_geneNameTable);
	for(i=0; i<numOfGenes; i++){
		fscanf(in_geneNameTable,"%s\t%i", correlTable[i].name, &correlTable[i].geneNum);
	}
	printf("[INFO] Finished loading gene names into memory.\n");
	fclose(in_geneNameTable);

	
	// Open cross-correlation table & load data
	in_crossCorrelation=fopen("cross_correlation_SRGs.txt","r");
	if(in_crossCorrelation==NULL){
		printf("[ERROR] Could not open input file cross_correlation_SRGs.txt. Terminating.\n");
		exit(1);
	}
	
	printf("[INFO] Loading correlation data into memory...");
	fflush(stdout);
	for(i=0; i<numOfGenes; i++){
		correl_max = 0;
		maxCorrel_gene_num = -1;
		for(j=0; j<numOfGenes; j++){
			if(fscanf(in_crossCorrelation,"%f",&correl) == EOF){
				printf("[ERROR] Reached premature end of file out_cross_correlation.txt. Terminating!\n");
				exit(1);
			}
			if(j!=i){ //ignore self-correlation
				if(fabs(correl)>correl_max){
					correl_max = fabs(correl);
					maxCorrel_gene_num = j;
				}
			}
		}
		correlTable[i].maxCorrel = correl_max;
		correlTable[i].correlatingGeneNum = maxCorrel_gene_num;
	}
	if(fscanf(in_crossCorrelation,"%*f") != EOF){
		printf("[WARNING] Did not reach end of out_cross_correlation.txt file!\n");
	}
	printf("Done.\n");
	
	
	
	// Figure out best mapping genes
	out = fopen("out_best_mapping_genes.txt","w");
	if(out==NULL){
		printf("[ERROR] Could not open output file out_best_mapping_genes.txt. Terminating.\n");
		exit(1);
	}
	fprintf(out,"Gene name\tMax Correlation\tCorrelating genes");


	genesLeft = 0;
	for(i=0; i<numOfGenes; i++){
		if(correlTable[i].maxCorrel > 0) genesLeft += 1;
	}
	printf("[INFO] %i genes have a max correl > 0.\n", genesLeft);
	
	correl_max = 1;
	while(genesLeft>1 && correl_max>CORREL_THRESHOLD){
		correl_max = 0;
		maxCorrel_gene_num = -1;
		//Find top correlating gene
		for(i=0; i<numOfGenes; i++){
			if(correlTable[i].geneNum != -1){ //gene has not been removed from list
				if(correlTable[i].maxCorrel > correl_max){
					correl_max = correlTable[i].maxCorrel;
					maxCorrel_gene_num = i;
				}
			}
		}
		fprintf(out,"\n%s\t%f",correlTable[maxCorrel_gene_num].name,correlTable[maxCorrel_gene_num].maxCorrel);
		removeGene(correlTable, maxCorrel_gene_num, numOfGenes, &genesLeft, out);

	}
	
	
	// Close files and free memory
	
	fclose(in_crossCorrelation);
	fclose(out);
	

}


void removeGene(struct correlTableType *correlTable, int geneNum, int totalNumOfGenes, int *genesLeft, FILE *out){
	int i;
	
	if(geneNum != -1){
	
		// remove this gene from the list
		fprintf(out,"\t%s", correlTable[geneNum].name);
		correlTable[geneNum].geneNum = -1;
		correlTable[geneNum].correlatingGeneNum = -1;
		*genesLeft = *genesLeft -1;
	
	
		// remove any gene that was correlating best with this gene
		for(i=0; i<totalNumOfGenes; i++){
			if(correlTable[i].correlatingGeneNum == geneNum && correlTable[i].maxCorrel>CORREL_THRESHOLD){
				removeGene(correlTable, i, totalNumOfGenes, genesLeft, out);
			}
		}
	}
}

