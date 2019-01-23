#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>



int main(int argc, char* argv[]){
	FILE *in, *in_mapping_genes, *out, *out_genes;
	int cell_num;
	int gene_num;
	int mapping_genes_num;
	int i,j,k,l;
	int found;
	char c;
	char *gene_names;
	float *reads;
	float correl;
	float mean_i, mean_j, numerator, denom_i, denom_j;
	int outlier;
	float max;
	
	struct correspondance {
		char name[40];
		int num;
		int num_in_seq_database;
	} *mapping_genes;

	in=fopen("expression_data.txt","r");
	if(in==NULL){
		printf("[ERROR] Could not open input file expression_data.txt. Terminating.\n");
		exit(1);
	}

	in_mapping_genes=fopen("mapping_genes.txt","r");
	if(in_mapping_genes==NULL){
		printf("[ERROR] Could not open input file mapping_genes.txt. Terminating.\n");
		exit(1);
	}
	
	out=fopen("cross_correlation.txt","w");
	if(out==NULL){
		printf("[ERROR] Could not open output file cross_correlation.txt. Terminating.\n");
		fclose(in);
		exit(1);
	}
	out_genes=fopen("cross_correlation_gene_name_table.txt","w");
	if(out_genes==NULL){
		printf("[ERROR] Could not open output file cross_correlation_gene_name_table.txt. Terminating.\n");
		fclose(in);
		fclose(out);
		exit(1);
	}
	
	
	//Figure out size of file and if it can be loaded into memory
	while((c=getc(in))!=13 && c!=EOF); // go to end of header line containing cell names
	cell_num=0;
	fscanf(in,"%*s"); //first gene name
	c=getc(in);
	while(c!=13 && c!= EOF){
		cell_num += 1;
		fscanf(in,"%*f");
		c=getc(in);
	}
	printf("[INFO] Data matrix contains %i cells.\n", cell_num);
	
	gene_num=1;
	while(fscanf(in,"%*s")!=EOF){
		gene_num += 1;
		while((c=getc(in))!=13 && c!=EOF); //go to end of line
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
	while((c=getc(in))!=13 && c!=EOF); // go to end of header line containing cell names 
	i=0;
	while(fscanf(in,"%39s",&gene_names[40*i])!=EOF){
		for(j=0; j<cell_num; j++){
			fscanf(in,"%f",&reads[cell_num*i+j]);
		}
		i+=1;
	}
	
	
	//Load mapping genes into memory
	mapping_genes_num=0;
	while(fscanf(in_mapping_genes,"%*s")!=EOF){
		mapping_genes_num += 1;
	}
	rewind(in_mapping_genes);
	printf("[INFO] %i mapping genes found.\n", mapping_genes_num);
	mapping_genes=malloc(mapping_genes_num*sizeof(struct correspondance));
	for(i=0; i<mapping_genes_num; i++){
		fscanf(in_mapping_genes,"%s", mapping_genes[i].name);
		mapping_genes[i].num = i;
		found = 0;
		j=0;
		while(!found && j<gene_num){
			if(!strcmp(mapping_genes[i].name,&gene_names[40*j])){
				mapping_genes[i].num_in_seq_database = j;
				found = 1;
			}
			j += 1;
		}
		if(!found){
			printf("[ERROR] mapping gene %s not found in sequencing database !\n Terminating!\n", mapping_genes[i].name);
			exit(1);
		}
	}
	
//for(j=0; j<cell_num; j++) printf("%f\t", reads[cell_num*2+j]);
//for(i=0; i<gene_num; i++) printf("%s\t", &gene_names[40*i]);
	
	
	//Calculate and output results
	for(i=0; i<gene_num; i++){
		fprintf(out_genes,"%s\t%i\n", &gene_names[40*i],i);
	}

	printf("[INFO] Computing cross-correlations for genes...\n");
	for(i=0; i<gene_num; i++){
		for(l=0; l<mapping_genes_num; l++){
			j=mapping_genes[l].num_in_seq_database;
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
//if(i==8631 && l==44) printf("%f\t%f\n",reads[cell_num*i+k],reads[cell_num*j+k]);
				if((reads[cell_num*i+k]-mean_i)*(reads[cell_num*j+k]-mean_j)>max){
					max=(reads[cell_num*i+k]-mean_i)*(reads[cell_num*j+k]-mean_j);
					outlier=k;
//if(i==8631 && l==44) printf("new max. max=%f outlier=%i\n",max,outlier);
				}
			}

//if(i==8631 && l==44) printf("outlier=%i", outlier);			
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
//if(i==8631 && l==44) printf("means=%f %f\n", mean_i, mean_j);			
			// calculate numerator
			numerator=0;
			for(k=0; k<cell_num; k++){
//if(i==8631 && l==44) printf("[%f][%f]\n",reads[cell_num*i+k],reads[cell_num*j+k]);
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
			if(l<(mapping_genes_num-1)){
				fprintf(out,"\t");
			} else {
				fprintf(out,"\n");
			}
		}
	}
	printf("[INFO] Done!\n");
	
	//Close and exit	
	fclose(in);
	fclose(out);
	fclose(out_genes);
}

