#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>



int main(int argc, char* argv[]){
	FILE *in, *out, *out_genes;
	int cell_num;
	int gene_num;
	int i,j,k;
	char c;
	char *gene_names;
	float *reads;
	float correl;
	float mean_i, mean_j, numerator, denom_i, denom_j;
	int outlier;
	float max;

	in=fopen("SRG_expression_data.txt","r");
	if(in==NULL){
		printf("[ERROR] Could not open input file SRG_expression_data.txt. Terminating.\n");
		exit(1);
	}
	
	out=fopen("cross_correlation_SRGs.txt","w");
	if(out==NULL){
		printf("[ERROR] Could not open output file cross_correlation_SRGs.txt. Terminating.\n");
		fclose(in);
		exit(1);
	}
	out_genes=fopen("cross_correlation_SRG_gene_name_table.txt","w");
	if(out_genes==NULL){
		printf("[ERROR] Could not open output file cross_correlation_SRG_gene_name_table.txt. Terminating.\n");
		fclose(in);
		fclose(out);
		exit(1);
	}
	
	//Figure out size of file and if it can be loaded into memory
	while((c=getc(in))!=10 && c!=13 && c!=EOF); // go to end of header line containing cell names
	cell_num=0;
	fscanf(in,"%*s"); //first gene name
	c=getc(in);
	while(c!=10 && c!=13 && c!= EOF){
		cell_num += 1;
		fscanf(in,"%*f");
		c=getc(in);
	}
	printf("[INFO] Data matrix contains %i cells.\n", cell_num);
	
	gene_num=1;
	while(fscanf(in,"%*s")!=EOF){
		gene_num += 1;
		while((c=getc(in))!=10 && c!=13 && c!=EOF); //go to end of line
	}
	printf("[INFO] Data matrix contains %i genes.\n", gene_num);
	
	rewind(in);
	
	// Load data into memory
	i = (gene_num * sizeof(char) * 40 + gene_num*cell_num*sizeof(float))/1024/1024;
	printf("[USER INPUT] Loading data into memory will require %i MB of memory.\n", i);
	printf("[USER INPUT] Proceed (y/n)? ");
	scanf("%c",&c);
	if(c!='y'){
		printf("Terminating upon user request.\n");
		fclose(in);
		fclose(out);
		fclose(out_genes);
		exit(1);
	}
	
	gene_names=malloc(sizeof(char)*40*gene_num);
	if(gene_names==NULL){
		printf("[ERROR] Could not allocate memory for gene_names.\n Terminating.\n");
		fclose(in);
		fclose(out);
		fclose(out_genes);
		exit(1);
	}
	reads=malloc(sizeof(float)*gene_num*cell_num);
	if(reads==NULL){
		printf("[ERROR] Could not allocate memory for reads.\n Terminating.\n");
		fclose(in);
		fclose(out);
		fclose(out_genes);
		exit(1);
	}
	while((c=getc(in))!=10 && c!=13 && c!=EOF); // go to end of header line containing cell names 
	i=0;
	while(fscanf(in,"%39s",&gene_names[40*i])!=EOF){
		for(j=0; j<cell_num; j++){
			fscanf(in,"%f",&reads[cell_num*i+j]);
		}
		i+=1;
	}
	
//for(j=0; j<cell_num; j++) printf("%f\t", reads[cell_num*2+j]);
//for(i=0; i<gene_num; i++) printf("%s\t", &gene_names[40*i]);
	
	
	//Calculate and output results
	for(i=0; i<gene_num; i++){
		fprintf(out_genes,"%s\t%i\n", &gene_names[40*i],i);
	}

printf("Cross-correlations computed for gene:\n");
	for(i=0; i<gene_num; i++){
printf("%i of %i\n", i, gene_num);
		for(j=0; j<gene_num; j++){
			//calculate means for genes i and j
			mean_i=0;
			mean_j=0;
			for(k=0; k<cell_num; k++){
				mean_i += reads[cell_num*i+k];
				mean_j += reads[cell_num*j+k];
			}
			mean_i = mean_i/cell_num;
			mean_j = mean_j/cell_num;
			
			// identify outlier
			max=0;
			outlier=0;
			for(k=0; k<cell_num; k++){
				if((reads[cell_num*i+k]-mean_i)*(reads[cell_num*j+k]-mean_j)>max){
					max=(reads[cell_num*i+k]-mean_i)*(reads[cell_num*j+k]-mean_j);
					outlier=k;
				}
			}
			
			// recalculate mean without outlier
			mean_i=0;
			mean_j=0;
			for(k=0; k<cell_num; k++){
				if(k!=outlier){
					mean_i += reads[cell_num*i+k];					
					mean_j += reads[cell_num*j+k];
				}
			}
			mean_i = mean_i/(cell_num-1);
			mean_j = mean_j/(cell_num-1);
			
			// calculate numerator
			numerator=0;
			for(k=0; k<cell_num; k++){
				if(k!=outlier) numerator = numerator + (reads[cell_num*i+k]-mean_i)*(reads[cell_num*j+k]-mean_j);
			}
			
			// calculate denominator parts
			denom_i = 0;
			denom_j = 0;
			for(k=0; k<cell_num; k++){
				if(k!=outlier){
					denom_i = denom_i + (reads[cell_num*i+k]-mean_i)*(reads[cell_num*i+k]-mean_i);
					denom_j = denom_j + (reads[cell_num*j+k]-mean_j)*(reads[cell_num*j+k]-mean_j);
				}
			}
			
			// calculate correl coefficient
			if(denom_i*denom_j != 0){
				correl = numerator / sqrtf(denom_i*denom_j);
			} else {
				correl = 0;
			}
			
			//output
			fprintf(out,"%f", correl);
			if(j<(gene_num-1)){
				fprintf(out,"\t");
			} else {
				fprintf(out,"\n");
			}
		}
	}
	
	//Close and exit	
	fclose(in);
	fclose(out);
	fclose(out_genes);
}

