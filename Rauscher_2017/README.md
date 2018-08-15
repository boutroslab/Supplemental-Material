# Towards an Integrated Map of Genetic Interactions in Cancer Cells

The paper that this repository is related to can be viewed on [the Molecular Systems Biology journal website](http://msb.embopress.org/content/14/2/e7656) 

## Abstract

Cancer genomes often harbor hundreds of molecular aberrations. Such genetic variants can be drivers or passengers of tumorigenesis and create vulnerabilities for potential therapeutic exploitation. To identify genotype-dependent vulnerabilities, forward genetic screens in different genetic backgrounds have been conducted. We devised MINGLE, a computational framework to integrate CRISPR/Cas9 screens originating from different libraries building on approaches pioneered for genetic network discovery in model organisms. We applied this method to integrate and analyze data from 85 CRISPR/Cas9 screens in human cancer cells combining functional data with information on genetic variants to explore more than 2.1 million gene-background relationships. In addition to known dependencies, we identified new genotype-specific vulnerabilities of cancer cells. Experimental validation of predicted vulnerabilities identified GANAB and PRKCSH as new positive regulators of Wnt/β-catenin signaling. By clustering genes with similar genetic interaction profiles, we drew the largest genetic network in cancer cells to date. Our scalable approach highlights how diverse genetic screens can be integrated to systematically build informative maps of genetic interactions in cancer, which can grow dynamically as more data is included.

## Supporting analysis code for the manuscript

This directory contains an R markdown file that can reproduce the figures in the manuscript. A corresponding R package including all source data required to run the code can be downloaded from [Figshare](https://figshare.com/s/33f68e70fbf6e6ac600f). The package can then be installed from the command line by typing 

```{sh}
R CMD INSTALL CGIMhd17_0_1_0.tar.gz
```

or using for example [Rstudio](https://www.rstudio.com/). Once the package is installed you can view the package vignette describing the analysis in R.

```{r}
library(CGIMhd17)
vignette('CGIM_analysis')
```

## Contact

Should you encounter any issues or have any questions please contact Benedikt Rauscher <b.rauscher@dkfz.de>.
