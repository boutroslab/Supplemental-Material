# Time-resolved mapping of genetic interactions to model rewiring of signaling pathways

The paper that this repository is related to can be viewed on [the eLife journal website](https://elifesciences.org/articles/40174) 

## Abstract

Context-dependent changes in genetic interactions are an important feature of cellular pathways and their varying responses under different environmental conditions. However, methodological frameworks to investigate the plasticity of genetic interaction networks over time or in response to external stresses are largely lacking. To analyze the plasticity of genetic interactions, we performed a combinatorial RNAi screen in Drosophila cells at multiple time points and after pharmacological inhibition of Ras signaling activity. Using an image-based morphology assay to capture a broad range of phenotypes, we assessed the effect of 12768 pairwise RNAi perturbations in six different conditions. We found that genetic interactions form in different trajectories and developed an algorithm, termed MODIFI, to analyze how genetic interactions rewire over time. Using this framework, we identified more statistically significant interactions compared to end-point assays and further observed several examples of context-dependent crosstalk between signaling pathways such as an interaction between Ras and Rel which is dependent on MEK activity.

## Supporting data for the manuscript

This directory contains an R data-package that can reproduce the figures in the manuscript. The package can be downloaded from [Figshare](https://figshare.com/s/fe82824053056805032e). The package can then be installed from the command line by typing 

```{sh}
R CMD INSTALL MODIFIdata_0_1_0.tar.gz
```

Once this package is installed the vignette of the code package described below can be executed.

## Supporting analysis code for the manuscript

This directory contains an R package that can reproduce the figures in the manuscript. The package can be downloaded from the GitHub repository by clicking on the package file ('Modifi_0.1.0.tar.gz') and then clicking the 'Download' button on the right. The package can then be installed from the command line by typing 

```{sh}
R CMD INSTALL MODIFIanalysis_0_1_0.tar.gz
```

or using for example [Rstudio](https://www.rstudio.com/). Once the package is installed you can view the package vignette describing the analysis in R.

```{r}
library(MODIFIanalysis)
vignette('MODIFIanalysis')
```
all data from these gene-drug-interaction screens were analysed together:

see scripts at Modifi_analysis/inst/extdata:

1.	all_in_one_v1.3.clust.analyze.pl		#automated data handling pipeline to analyse all suitable images within a set of subdirectories
2.	image_analysis_ERC.v3.R					#image analysis pipeline input: 3 channel image set for one field of view; output: feature vectors for every single cell 
3.	extract_data.pl							#script to extract barcode meta-data from filenames
4.	collect_RData_files.R					#script to collect all single cell data tables as trimmed mean vectors in one big dataframe

all data from these gene-gene-drug-interaction screens were analysed together:

see scripts at Modifi_analysis/inst/extdata:

1.	all_in_one_v1.6.clust.analyze.pl		#automated data handling pipeline to analyse all suitable images within a set of subdirectories
2.	image_analysis_ERC.v6.R					#image analysis pipeline input: 3 channel image set for one field of view; output: feature vectors for every single cell 
3.	extract_data.pl							#script to extract barcode meta-data from filenames
4.	collect_RData_files.R					#script to collect all single cell data tables as trimmed mean vectors in one big dataframe

## Contact

Should you encounter any issues or have any questions please contact Florian Heigwer <f.heigwer@dkfz.de>.
