# A Pan-Cancer Analysis of Tumor Cell Lineage Dependencies

## Abstract

Tumor phenotypes are closely associated with their developmental lineage and cell of origin. However, tumor lineage-specific genetic vulnerabilities remain sparsely characterized. In this work, we inferred lineage-dependencies across 21 different tumor types based on genome-scale CRISPR screening data. Our analysis identified 1653 lineage-specific essential genes, many of which have roles in signaling and development. Several tumor types showed resistance to perturbation of these lineage-specific essential genes, if they expressed gene signatures associated with dedifferentiation or epithelial to mesenchymal transition. Accordingly, decreased expression of the developmental transcription factors KLF5, HNF4A and CDX2 was associated with an increased resistance to Wnt-signaling perturbation in colorectal cancer. We further show that these transcription factors and the Wnt-signalling effector TCF7L2 co-regulate many target genes. Our results suggest that cooperations between mutated signaling pathways and lineage-specific transcription factors mediate the outcome of aberrant signaling activity across a diverse range of tumor lineages. These interactions can determine whether targeted pathway inhibition will be effective in a particular cancer type.

## Supporting analysis code for the manuscript

This directory contains annotated R code that can reproduce analyses and figures in the manuscript "A Pan-Cancer Analysis of Tumor Cell Lineage Dependencies". A corresponding R package including all source data required to run the code can be downloaded from [Figshare](https://figshare.com/s/cb5c58f84e3870817f65). The package can then be installed from the command line by typing 

```{sh}
R CMD INSTALL HDCRC2019_0_1_0.tar.gz
```

or using for example [Rstudio](https://www.rstudio.com/). Once the package is installed you can view the package vignette describing the analysis in R.

```{r}
library(HDCRC2019)
vignette('hdcrc2019')
```

## Contact

Should you encounter any issues or have any questions please contact Benedikt Rauscher <b.rauscher@dkfz.de>.
