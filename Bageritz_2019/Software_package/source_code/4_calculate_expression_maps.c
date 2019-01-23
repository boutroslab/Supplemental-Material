#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

void WriteHexString(FILE *fptr,char *s);
void WriteTIFFfile(char *geneName, int width, int height, float *pixels);


int main(int argc, char* argv[]){
	FILE *in_genelist, *in_mapping_genes, *in_map, *in_correlations, *in_genesToMap;
	char gene_name[40];
	char s[40];
	int query_gene_index;
	int mapping_gene_num;
	int i, j, k;
	char c;
	float *correlations;
	int map_call;
	float score;
	float *map;
	int num_genes_to_map;
	int found;
	
	struct gene_list{
		char name[40];
		int found;
	} *genes_to_map;
	
	#define MAP_WIDTH 260
	#define MAP_HEIGHT 360



	//allocate memory for map
	if((map = malloc(sizeof(float)*MAP_WIDTH*MAP_HEIGHT))==NULL){
		printf("[ERROR] Could not allocate memory for map data. Terminating.\n");
		exit(1);
	}

	//open files
	if((in_genelist=fopen("cross_correlation_gene_name_table.txt","r"))==NULL){
		printf("[ERROR] Could not open input file cross_correlation_gene_name_table.txt. Terminating.\n");
		exit(1);
	}
	if((in_mapping_genes=fopen("mapping_genes.txt","r"))==NULL){
		printf("[ERROR] Could not open input file cross_correlation_mapping_genes.txt. Terminating.\n");
		fclose(in_genelist);
		exit(1);
	}
	if((in_map=fopen("combined_map.txt","r"))==NULL){
		printf("[ERROR] Could not open input file combined_map.txt. Terminating.\n");
		exit(1);
	}
	if((in_correlations=fopen("cross_correlation.txt","r"))==NULL){
		printf("[ERROR] Could not open input file cross_correlation.txt. Terminating.\n");
		exit(1);
	}


	//count mapping genes
	mapping_gene_num=0;
	while(fscanf(in_mapping_genes,"%*s")!=EOF){
		mapping_gene_num += 1;
	}
	rewind(in_mapping_genes);
	printf("[INFO] Found %i mapping genes in file mapping_genes.txt.\n",mapping_gene_num);
	
	//check mapping genes are in same order in two files
	fscanf(in_map,"%*s\t%*s"); //skip first two column names
	for(i=0; i<mapping_gene_num; i++){
		fscanf(in_map,"%s",s);
		fscanf(in_mapping_genes,"%s",gene_name);
		if(strcmp(s,gene_name)){
			printf("[ERROR] List of mapping genes in combined_map.txt does not correspond to list in cross-correlation table. Terminating!\n");
			exit(1);
		}
	}
	c=getc(in_map);
	if(c!=10){
		printf("[ERROR] List of mapping genes in combined_map.txt is longer than the mapping genes in cross_correlation_mapping_genes.txt. Terminating\n");
		exit(1);
	}

	//check map fits with given width and height
	i=0;
	rewind(in_map);
	while(getc(in_map)!=10); //go to end of header line
	while(fscanf(in_map,"%*i")!=EOF){
		i+=1;
		while(getc(in_map)!=10);
	}
	if(i!=MAP_WIDTH*MAP_HEIGHT){
		printf("[ERROR] Map height & width do not fit available data in combined_map.txt. Terminating.\n");
		exit(1);
	}
	
	//check user gave a valid file name with gene list
	if(argc != 2){
		printf("[ERROR] No input file name containing list of genes to map found!\n");
		printf("USAGE: expression_map [name of file with list of gene names to map]. Terminating.\n");
		exit(1);
	}
	if((in_genesToMap=fopen(argv[1],"r"))==NULL){
		printf("[ERROR] Could not open input file %s. Terminating.\n", argv[1]);
		exit(1);
	}
	
	//input list of genes to map
	num_genes_to_map = 0;
	while(fscanf(in_genesToMap,"%39s", gene_name)!=EOF){
		num_genes_to_map += 1;
	}
	rewind(in_genesToMap);
printf("[INFO] Found %i genes to map in input file.\n", num_genes_to_map);
	if((genes_to_map = malloc(sizeof(struct gene_list)*num_genes_to_map))==NULL){
		printf("[ERROR] Could not allocate memory for gene_list. Terminating.\n");
		exit(1);
	}
	i=0;
	while(fscanf(in_genesToMap,"%39s", gene_name)!=EOF){
		strcpy(genes_to_map[i].name, gene_name);
		genes_to_map[i].found = 0;
		i += 1;
	}
	
	
	//Allocate memory for correlation data
	if((correlations = malloc(sizeof(float)*mapping_gene_num))==NULL){
		printf("[ERROR] Could not allocate memory for correlation data. Terminating.\n");
		exit(1);
	}

	//Make directory to save output maps
	system("mkdir output_absolute_maps_directory");
	
	//Make maps
	while(fscanf(in_genelist,"%s\t%i",gene_name,&query_gene_index)!=EOF){
	
		//check if it's in the list of genes to map
		found = 0;
		for(i=0; i<num_genes_to_map && found==0; i++){
			if(!strcmp(genes_to_map[i].name, gene_name)){
				found = 1;
				genes_to_map[i].found = 1;
			}
		}
		if(found == 0){
			while((c=getc(in_correlations)) != 10 && c!=EOF); // go to next row
		} else {
			for(i=0; i<mapping_gene_num; i++){
				fscanf(in_correlations,"%f",&correlations[i]);
			}
			while((c=getc(in_correlations)) != 10 && c!=EOF); // go to end of row
	
			//Calculate probability
			//NOTE : STILL NEED TO NORMALIZE FOR TOTAL EXPRESSION LEVELS !!
	
			
			rewind(in_map);
			while(getc(in_map)!=10); //go to end of header line
			for(i=0; i<MAP_HEIGHT; i++){
				for(j=0; j<MAP_WIDTH; j++){
					fscanf(in_map,"%*i"); // cell number
					fscanf(in_map,"%i",&map_call); // in wing disc?
					if(map_call==0){
						map[MAP_WIDTH*i+j]=0;
						while(getc(in_map)!=10); // go to end of this line
					} else {
						score=0;
						for(k=0; k<mapping_gene_num; k++){
							fscanf(in_map,"%i",&map_call);
							if(map_call==0){ //mapping gene not expressed in this cell
								score -= correlations[k];
							}else{
								score += correlations[k];
							}
						}
						map[MAP_WIDTH*i+j]=score;
					}
				}
			}
			WriteTIFFfile(gene_name, MAP_WIDTH, MAP_HEIGHT, map);
		}
	}
	
	//Check which genes were not found
	j=0;
	for(i=0; i<num_genes_to_map; i++){
		if(genes_to_map[i].found ==0){
			printf("[ERROR] Did not find gene %s!\n", genes_to_map[i].name);
		} else {
			j+=1;
		}
	}
	printf("[INFO] Found %i of %i genes in input list to map.\n", j, num_genes_to_map);

	//Close and exit	
	free(map);
	free(correlations);
	fclose(in_genelist);
	fclose(in_mapping_genes);
	fclose(in_map);
	fclose(in_correlations);
	fclose(in_genesToMap);
}

void WriteHexString(FILE *fptr,char *s)
{
   unsigned int i,c;
   char hex[3];

   for (i=0;i<strlen(s);i+=2) {
      hex[0] = s[i];
      hex[1] = s[i+1];
      hex[2] = '\0';
      sscanf(hex,"%X",&c);
      putc(c,fptr);
   }
}

void WriteTIFFfile(char *geneName, int width, int height, float *pixels){
	char filename[150];
	FILE *out;
	float min, max, range;
	int i, j, pix;
	int offset;

	
	strcpy(filename, "output_absolute_maps_directory/map_");
	strcat(filename,geneName);
	strcat(filename, ".tiff");
	
	if((out=fopen(filename,"w"))==NULL){
		printf("[ERROR] Could not open output file %s. Terminating.\n", filename);
		exit(1);
	}

	// NORMALIZE VALUES TO RANGE 0-255
	min=pixels[0];
	max=pixels[0];
	for(i=0; i<width*height; i++){
		if(pixels[i]<min) min=pixels[i];
		if(pixels[i]>max) max=pixels[i];
	}
	
	if(min<-5) printf("[WARNING] Min pixel value for gene %s (%f) is less than -5!\n", geneName, min);
	if(max>5) printf("[WARNING] Max pixel value for gene %s (%f) is greater than +5!\n", geneName, max);
	min = -5;
	max = 5;
	
	range=max-min;
	for(i=0; i<width*height; i++){
		if(pixels[i]){ // exactly 0 means not in wing disc -> leave unchanged
			if(pixels[i]<-5) pixels[i]=-5; //for using an absolute pixel range
			if(pixels[i]>5) pixels[i]=5; //for using an absolute pixel range
			pixels[i] = (pixels[i]-min)/range*255;
		}
	}


/* Write the header */
   WriteHexString(out,"4d4d002a");    /* Big endian & TIFF identifier */
   offset = width * height * 3 + 8;
   putc((offset & 0xff000000) / 16777216,out);
   putc((offset & 0x00ff0000) / 65536,out);
   putc((offset & 0x0000ff00) / 256,out);
   putc((offset & 0x000000ff),out);

   /* Write the binary data */
   for (i=0;i<height;i++) {
      for (j=0;j<width;j++) {
      	if(pixels[i*width + j]==0){
			fputc(255,out);
			fputc(255,out);
			fputc(255,out);
      	} else {
			pix = pixels[i*width + j];
			fputc(255-pix*235/255,out);
			fputc(255-pix*245/255,out);
			fputc(255-pix*131/255,out);
		}
      }
   }

   /* Write the footer */
   WriteHexString(out,"000e");  /* The number of directory entries (14) */

   /* Width tag, short int */
   WriteHexString(out,"0100000300000001");
   fputc((width & 0xff00) / 256,out);    /* Image width */
   fputc((width & 0x00ff),out);
   WriteHexString(out,"0000");

   /* Height tag, short int */
   WriteHexString(out,"0101000300000001");
   fputc((height & 0xff00) / 256,out);    /* Image height */
   fputc((height & 0x00ff),out);
   WriteHexString(out,"0000");

   /* Bits per sample tag, short int */
   WriteHexString(out,"0102000300000003");
   offset = width * height * 3 + 182;
   putc((offset & 0xff000000) / 16777216,out);
   putc((offset & 0x00ff0000) / 65536,out);
   putc((offset & 0x0000ff00) / 256,out);
   putc((offset & 0x000000ff),out);

   /* Compression flag, short int */
   WriteHexString(out,"010300030000000100010000");

   /* Photometric interpolation tag, short int */
   WriteHexString(out,"010600030000000100020000");

   /* Strip offset tag, long int */
   WriteHexString(out,"011100040000000100000008");

   /* Orientation flag, short int */
   WriteHexString(out,"011200030000000100010000");

   /* Sample per pixel tag, short int */
   WriteHexString(out,"011500030000000100030000");

   /* Rows per strip tag, short int */
   WriteHexString(out,"0116000300000001");
   fputc((height & 0xff00) / 256,out);
   fputc((height & 0x00ff),out);
   WriteHexString(out,"0000");

   /* Strip byte count flag, long int */
   WriteHexString(out,"0117000400000001");
   offset = width * height * 3;
   putc((offset & 0xff000000) / 16777216,out);
   putc((offset & 0x00ff0000) / 65536,out);
   putc((offset & 0x0000ff00) / 256,out);
   putc((offset & 0x000000ff),out);

   /* Minimum sample value flag, short int */
   WriteHexString(out,"0118000300000003");
   offset = width * height * 3 + 188;
   putc((offset & 0xff000000) / 16777216,out);
   putc((offset & 0x00ff0000) / 65536,out);
   putc((offset & 0x0000ff00) / 256,out);
   putc((offset & 0x000000ff),out);

   /* Maximum sample value tag, short int */
   WriteHexString(out,"0119000300000003");
   offset = width * height * 3 + 194;
   putc((offset & 0xff000000) / 16777216,out);
   putc((offset & 0x00ff0000) / 65536,out);
   putc((offset & 0x0000ff00) / 256,out);
   putc((offset & 0x000000ff),out);

   /* Planar configuration tag, short int */
   WriteHexString(out,"011c00030000000100010000");

   /* Sample format tag, short int */
   WriteHexString(out,"0153000300000003");
   offset = width * height * 3 + 200;
   putc((offset & 0xff000000) / 16777216,out);
   putc((offset & 0x00ff0000) / 65536,out);
   putc((offset & 0x0000ff00) / 256,out);
   putc((offset & 0x000000ff),out);

   /* End of the directory entry */
   WriteHexString(out,"00000000");

   /* Bits for each colour channel */
   WriteHexString(out,"000800080008");

   /* Minimum value for each component */
   WriteHexString(out,"000000000000");

   /* Maximum value per channel */
   WriteHexString(out,"00ff00ff00ff");

   /* Samples per pixel for each channel */
   WriteHexString(out,"000100010001");


	fclose(out);
	return;
}


