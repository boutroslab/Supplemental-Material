# Pooled CRISPR screening at high sensitivity with an empirically designed sgRNA library

## Abstract

Given their broad utility in functionally annotating genomes, the experimental design of genome-scale CRISPR screens can vary greatly and criteria for optimal experimental implementation and library composition are still emerging. In this study, we report advantages of conducting viability screens in selected Cas9 single cell clones in contrast to Cas9 bulk populations. We further systematically analyzed published CRISPR screens in human cells to identify single-guide (sg)RNAs with consistent high on-target and low off-target activity. Selected guides were collected in a new genome-scale sgRNA library, which efficiently identifies core and context-dependent essential genes. In summary, we show how empirically designed libraries in combination with an optimised experimental design increase the dynamic range in gene essentiality screens at reduced library coverage.

## Supporting analysis code for the manuscript

This directory contains annotated R code that can reproduce analyses and figures in the manuscript "Pooled CRISPR screening at high sensitivity with an empirically designed sgRNA library". A corresponding R package including all source data required to run the code can be downloaded from Figshare [under this link](https://figshare.com/s/4cd0a152aa0109cce5a0). The package can then be installed from the command line by typing

```{sh}
R CMD INSTALL HDCRISPR2019_0_1_0.tar.gz
```

or using for example [Rstudio](https://www.rstudio.com/). Once the package is installed you can view the package vignette describing the analysis in R.

```{r}
library(HDCRISPRC2019)
browseVignettes('HDCRISPR2019')
```

## Contact

Should you encounter any issues or have any questions please contact Benedikt Rauscher <b.rauscher@dkfz.de>.
