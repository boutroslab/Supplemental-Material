# Multi-omics integration identifies a selective vulnerability of colorectal cancer subtypes to YM155

## Abstract

Tumor heterogeneity is a major challenge to the treatment of colorectal cancer (CRC). Recently, a transcriptome-based classification was developed, segregating CRC into four consensus molecular subtypes (CMS) with distinct biological and clinical characteristics. Here, we applied the CMS classification on CRC cell lines to identify novel subtype-specific drug vulnerabilities. We combined publicly available transcriptome data from multiple resources to assign 157 CRC cell lines to CMS. By integrating results from large-scale drug screens, we discovered that the CMS1 subtype is highly vulnerable to the BIRC5 suppressor YM155. We confirmed our results using an independent panel of CRC cell lines and demonstrated a 100-fold higher sensitivity of CMS1. This vulnerability was specific to YM155 and not observed for commonly used chemotherapeutic agents. In CMS1 CRC, low concentrations of YM155 induced apoptosis and expression signatures associated with ER stress-mediated apoptosis signaling. Using a genome-wide CRISPR/Cas9 screen, we further discovered a novel role of genes involved in LDL-receptor trafficking as modulators of YM155 sensitivity in the CRC cell line HCT116. Our work shows that combining drug response data with CMS classification in cell lines can reveal selective vulnerabilities and proposes YM155 as a novel subtype-specific drug.

## Supporting computer code

This directory contains annotated R code that can reproduce analyses and figures in the manuscript "Multi-omics integration identifies a selective vulnerability of colorectal cancer subtype to YM155" published in [Molecular Oncology](https://onlinelibrary.wiley.com/doi/10.1002/ijc.33393). A corresponding R package that includes all source data required to run the code can be downloaded from [Figshare](https://figshare.com/s/aad4f51b882f0117ef4c). The package can then be installed from the command line by typing

```{sh}
R CMD INSTALL CMSYM1552018_0.1.0.tar.gz
```

or using for example [Rstudio](https://www.rstudio.com/). Once the package is installed you can view the package vignette describing the analysis in R.

```{r}
library(CMSYM1552018)
browseVignettes('CMSYM1552018')
```

