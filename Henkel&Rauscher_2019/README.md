# Pooled CRISPR screening with high sensitivity using empirically designed sgRNAs

## Abstract

Large-scale pooled CRISPR/Cas9 screens are powerful tools to determine gene essentiality in various contexts. By this means, functional dependencies have been interrogated in hundreds of mammalian cell lines until today. However, screening designs vary greatly and optimal criteria for library composition and experimental implementation still require further investigation. In this study, we systematically analyzed previously published CRISPR screens in human cells to identify single-guide (sg)RNAs with consistent high on-target and low off-target activity. Based on selected guides, we generated a new genome-scale sgRNA library and assessed its performance by gene essentiality screening in the near-haploid human HAP1 cell line. Our library achieved near-optimal results at distinguishing core- and nonessential genes and avoided off-targets of previous libraries. Moreover, our screens revealed so far undescribed context-specific dependencies of HAP1 cells on the Fanconi anemia pathway and the pluripotency factors SOX2 and POU5F1 (Oct4), resembling functional dependencies of embryonic stem cells. When comparing hit calling in a Cas9 bulk population and two single cell clones, we observed stronger depletion phenotypes in single cell clones enabling essential gene identification at a reduced library coverage. In summary, we describe a highly active CRISPR/Cas9 library, whose design is based on prior information of previously published sgRNA phenotypes. Our library in combination with an optimised experimental design increases the dynamic range in gene essentiality screens at reduced library coverage. 

## Supporting analysis code for the manuscript


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
