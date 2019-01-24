# Gene expression maps from single-cell sequencing data using gene expression correlations

# Contents
1. Overview
2. Repo contents
3. System Requirements
4. Installation Guide
5. Instructions for use
6. Demo





# 1. Overview

This software package accompanies the publication "Gene expression atlas of a developing tissue by single cell expression correlation analysis" by Josephine Bageritz, Philipp Willnow, Erica Valentini, Svenja Leible, Michael Boutros, and Aurelio A. Teleman, available either in bioRXiv (https://doi.org/10.1101/477125) or [NEED TO PUT IN HERE JOURNAL CITATION].

The purpose of this software package is to start with a gene expression matrix from single-cell sequencing data of a dissociated tissue, and to reconstruct a 2D map of gene expression in the tissue.





# 2. Repo contents

source_code: files with source code written in C for all applications required in this package

macOS_binary: compiled applications to run on MacOS X

sample_data: the data used in the publication mentioned above as sample data to run the software on





# 3. System requirements

## Hardware requirements

The compiled software runs on a standard computer with little required RAM (<100 MB). The runtimes below are for a computer with 16GB RAM and a 2.6 GHz Intel Core i7 (although only one core gets used).

## OS requirements

The macOS binaries have been tested on a system running MacOSX versions 10.12 and 10.13. The source code can be compiled and run on any system with a C compiler.





# 4. Installation Guide

## MacOS binaries

Simply copy the files onto the computer, and run them from the MacOS Terminal. Note that if they are not placed in the bin folder, you need to change directory to the location of the file you want to execute, and then type in the following to execute it:

./NameOfFileToExecute

## Source code files

Copy the files to the computer, compile them with a C compiler (e.g. GNU C Compiler) and then execute them.

This is how you compile them in linux (tested in Ubuntu):

```{bash}
unix$ cd source_code

unix$ gcc 1_cross_correlation_SRGs.c -o 1_cross_correlation_SRGs -lm

unix$ chmod a+x 1_cross_correlation_SRGs

unix$ gcc 2_identify_best_mapping_genes.c -o 2_identify_best_mapping_genes -lm

unix$ chmod a+x 2_identify_best_mapping_genes

unix$ gcc 3_cross_correlation_to_mapping_genes.c -o 3_cross_correlation_to_mapping_genes

unix$ chmod a+x 3_cross_correlation_to_mapping_genes

unix$ gcc 4_calculate_expression_maps.c -o 4_calculate_expression_maps.c -lm

unix$ chmod a+x 4_calculate_expression_maps
```

NOTE: The applications can't be compiled on a __Windows__ machine.

## Typical installation time

Installation of the MacOS binaries should take 5 minutes. Installing and compiling the source code files should take 10 minutes.





# 5. Instructions for use

## Application: 1_cross_correlation_all_genes

##### Purpose

This application generates a cross-correlation matrix of all genes against all genes in the gene expression matrix. This output will be used by the following application (2_identify_best_mapping_genes) to identify which ones are the best 'mapping genes' for the tissue being analyzed. Note that the correlation function used is the standard Pearson correlation, except that one outlier point is removed from the analysis.

##### Inputs

This application takes as input one file, called 'SRG_expression_data.txt' containing the gene expression matrix for all Spatially Restricted Genes (SRGs). Each row contains a gene, each column a cell. The contents should be raw UMIs that are log-transformed after adding 1 to the UMI count [ln(UMI+1)]. The SRGs can be identified following the R markdown instructions included in this package from the complete expression matrix of all genes. Only cells with at least 2000 UMIs (total) per cell should be included. The format of the file should be:

- tab delimited
- have a Carriage Return (CR, ascii code 13) or CR/LF (10+13) as end-of-line characters 
- the first row contains a list of cell identifiers (each as a single string, no spaces)
- the first column contains a list of gene names (each as a single string, no spaces)
- the table should be rectangular - every column should have a header. So the first cell (position 0,0 or cell A1 in Excel) should contain some text as a header for the gene name column (e.g. 'gene')
- the values in the matrix should use a dot (.) as a decimal marker

##### Output

The application will show its progress on the screen, as the number of genes for which it has calculated the correlation (e.g. 130 of 824).

The following files will be output:

- cross_correlation_SRGs.txt: a cross-correlation table with correlation coefficients for all SRGs against all SRGs (a square table). This table does not contain column or row names.
- cross_correlation_SRG_gene_name_table.txt: a list of all the SRG names in the order they appear in the file "cross_correlation_SRGs.txt"

##### Expected Runtime:

The circa 8 seconds for 800 SRGs. The runtime will increase exponentially with the number of SRGs.



## Application: 2_cross_correlation_all_genes

##### Purpose

This application uses the cross-correlation matrix of all SRGs against each other generated by application 1_cross_correlation_all_genes to identify the best 'mapping genes' to perform in situs on your tissue of interest.

##### Inputs

This application takes as input the two files generated by application 1_cross_correlation_all_genes (above), namely:

- cross_correlation_SRGs.txt: a cross-correlation table with correlation coefficients for all SRGs against all SRGs (a square table). This table does not contain column or row names.
- cross_correlation_SRG_gene_name_table.txt: a list of all the SRG names in the order they appear in the file "cross_correlation_SRGs.txt"

##### Output

This outputs a file called "out_best_mapping_genes.txt" with the following contents: The first column is the list of optimal 'mapping genes' whose expression patterns should be determined by in situ. These are genes that show high correlations to other genes expressed in this tissue, but are not highly-correlated to each other. The second column is the correlation coefficient of the mapping gene to the gene it is most correlated to. The following columns are the genes that have correlation coefficients >=0.3 to this mapping gene.

##### Expected Runtime:

<1 second



## Application: 3_cross_correlation_to_mapping_genes

##### Purpose

This application generates a cross-correlation matrix of all genes to all 'mapping genes' which will be used to generate gene expression maps of the tissue.

##### Inputs

This application takes two files as inputs:

- expression_data.txt:  This file contains the gene expression matrix for all genes. Each row contains a gene, each column a cell. The contents should be raw UMIs that are log-transformed after adding 1 to the UMI count [ln(UMI+1)]. Only cells with at least 2000 UMIs (total) per cell should be included. The format of the file should be:
  - tab delimited
  - have a Carriage Return (CR, ascii code 13) or CR/LF (10+13) as end-of-line characters 
  - the first row contains a list of cell identifiers (each as a single string, no spaces)
  - the first column contains a list of gene names (each as a single string, no spaces)
  - the table should be rectangular - every column should have a header. So the first cell (position 0,0 or cell A1 in Excel) should contain some text as a header for the gene name column (e.g. 'gene')
  - the values in the matrix should use a dot (.) as a decimal marker
- mapping_genes.txt: A table with one column listing the names of the mapping genes. The names should be identical to the names of the mapping genes as they appear in the file expression_data.txt. The column has no column name / header.

##### Outputs

This application creates two output files:

- cross_correlation.txt: a cross-correlation table with correlation coefficients for all genes against all mapping genes. This table does not contain column or rownames. The rows correspond to all genes in the expression_data.txt file. All columns correspond to the mapping genes in the order listed in the input file mapping_genes.txt
- cross_correlation_gene_name_table.txt: a list of all the gene names in the order they appear in the file "cross_correlation.txt"

(In other words, the list of genes in the input file "mapping_genes.txt" corresponds to the column names in cross_correlation.txt, and the list of genes in cross_correlation_gene_name_table.txt corresponds to the row names in cross_correlation.txt).

##### Expected Runtime:

Circa 10 seconds for 60 mapping genes, and 14.000 genes x 600 cells in the gene expression matrix.



## Application: 4_calculate_expression_maps

##### Purpose

This application calculates gene expression maps based on the cross-correlations to mapping genes (generated by application 3_cross_correlation_to_mapping_genes above) and on a map of which mapping gene is expressed where in the tissue. It outputs TIFF images of gene expression.

##### Inputs

This application takes five files as inputs:

- mapping_genes.txt: This is the same file as application 3_cross_correlation_to_mapping_genes takes as input. It contains a table with one column listing the names of the mapping genes. The names should be identical to the names of the mapping genes as they appear in the file expression_data.txt. The column has no column name / header.

- cross_correlation.txt: This is the output file from application 3_cross_correlation_to_mapping_genes. It contains a cross-correlation matrix of all genes to all mapping genes, without column or row names.

- cross_correlation_gene_name_table.txt: This is the second output file from application 3_cross_correlation_to_mapping_genes. It contains a list of all the gene names in the order they appear in the file "cross_correlation.txt"

- combined_map.txt: This is a map of which "mapping gene" is expressed where in the tissue of interest. The output images will be generated as TIFF files that are 260 pixels wide and 360 pixels high. These parameters can be modified in the source-code where they are defined as "#define MAP_WIDTH 260" and "#define MAP_HEIGHT 360". Unless these are modified, the file should have the following format:

  - tab delimited
  - have a Line Feed (LF, ascii code 10) or CR/LF (10+13) as end-of-line characters 
  - The first row contains column names / headers
  - The first column contains the numbers from 0 to 93599 in sequential order, corresponding to the pixel number in the image. The pixels are counted starting in the upper left corner of the image, moving to the right until the end of row is reached, and then moving in a similar fashion to the next line. Since the image is 260x360 pixels, there are 93600 pixels in total. See below for details how to generate this map.
  - The second column contains information about whether each pixel corresponds to a spot in the tissue of interest, or to the background (no tissue / the 'slide' if this were a real in situ). Background pixels should have value 0. Pixels containing tissue should be >0. If following the instructions below, ImageJ of Fiji will output 255 (the maximum value for an 8-bit TIFF image).
  - From the third column onwards, they contain equivalent expression data for whether each mapping gene is expressed in that pixel or not. Not expressed =0. Expressed = 255.
  - The first row contains column headers, which should be as follows
    - Col 1 = "pixel_nr"
    - Col 2 = "tissue"
    - Col 3 onwards = the exact gene name of the mapping gene as they appear in the other files

  One way to generate this file is as follows, but this will depend on the individual application. Create an image file (e.g. photoshop) that is 260 pixels wide x 360 pixels high. On this image define the region/shape of the tissue by coloring the region black. Create additional layers on top, each layer containing information for one mapping gene. In each case, indicate the region where this gene is expressed. This can be done by pasting in the picture of an actual in situ. Then export each layer as a TIFF (not compressed), open it in ImageJ or Fiji, threshold it to identify the region containing the tissue or the gene expression domain. Convert the thresholded region to a mask, which turns it into a binary image (with pixels of value 0 outside the expression domain, and value 255 inside the expression domain). This can then be exported with File > Save as... > Text Image as a number matrix. This matrix then needs to be converted into a single column of numbers (e.g. using the OFFSET of INDEX functions in excel).

- The last file can have any name. It should contain a list of genes for which expression maps should be calculated. The list of gene names should be separated by white-space characeters (e.g. one gene on each line), and the names should be identical to how they appear in the other files. In the sample data provided with this package, the file name is called "list_of_genes_to_map.txt". This filename needs to be provided as the first command line arguement when calling the application (e.g. ./4_calculate_expression_maps list_of_genes_to_map.txt )

##### NOTE:

This application makes a system call to "mkdir" to generate a directory to place the output files into. If the source code is compiled on a windows system, this statement will need to be adjusted accordingly (or deleted).

##### How to call the function (e.g. from MacOSX Terminal)

./4_calculate_expression_maps [name of file containing the list of genes to calculate maps of]

##### Outputs

- Screen output: This application calculates an expression value for genes at every pixel of the image. Values of -5 are rendered white in the final TIFF image and values of +5 are rendered dark purple. This seems to work fine for most sequencing data. In some cases, the calculated expression values will be significantly outside the range of -5 to +5. If this is the case, a warning will be displayed on the screen. In most cases the resulting image still look fine. In case not, these parameter should be adjusted in the code, lines 240 to 260.

- TIFF files: a directory called "output_absolute_maps_directory" will be generated. Inside this directory will be TIFF files with expression maps, one for each gene.

##### Expected Runtime:

Circa 1 second per TIFF file generated.



# 6. Demo

Demo input files and output files are provided in the folder "sample_data". These are the actual data files used to generate the figures in the publication. The applications can be tested as follows on a MacOS system:

```{bash}

unix$ cd sample_data

unix$ cd 1_cross_correlation_SRGs

unix$ ./1_cross_correlation_SRGs

unix$ cd ..

unix$ cd 2_identify_best_mapping_genes

unix$ ./2_identify_best_mapping_genes

unix$ cd ..

unix$ cd 3_cross_correlation_to_mapping_genes

unix$ ./3_cross_correlation_to_mapping_genes

unix$ cd ..

unix$ cd 4_calculate_expression_maps

unix$ ./4_calculate_expression_maps list_of_genes_to_map.txt

```
