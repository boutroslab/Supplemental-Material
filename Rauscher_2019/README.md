# Lineage specific core-regulatory circuits determine gene essentiality in cancer cells

## Abstract

Cancer cells rely on dysregulated gene expression programs to maintain their malignant phenotype. A cell’s transcriptional state is controlled by a small set of interconnected transcription factors that form its core-regulatory circuit (CRC). Previous work in pediatric cancers has shown, that disruption of the CRC by genetic alterations causes tumor cells to become highly dependent on its components creating new opportunities for therapeutic intervention. However, the role of CRCs and the mechanisms by which they are controlled remain largely unknown for most tumor types. Here, we developed a method to systematically predict ‘functional’ CRCs and associated biological processes from context-dependent essentiality data sets. Analysis of genome-scale CRISPR-Cas9 screens in 558 cancer cell lines showed that most tumor types specifically depend on a small number of transcription factors for proliferation. We found that these transcription factors compose the CRCs in these tumor types. Moreover, they are frequently altered in patient tumor samples indicating their oncogenic potential. Finally, we show that biological processes associated with each CRC are revealed by analyzing codependency between lineage-specific essential genes. Our results demonstrate that genetic addiction to lineage-specific core transcriptional mechanisms occurs across a broad range of tumor types. We exploit this phenomenon to systematically infer CRCs from lineage specific gene essentiality. Furthermore, our findings shed light on the selective genetic vulnerabilities that arise as the consequence of transcriptional dysregulation in different tumor types and show how the plasticity of regulatory circuits might influence drug resistance and metastatic potential.

## Supporting analysis code for the manuscript

This directory contains annotated R code that can reproduce analyses and figures in the manuscript "Lineage specific core-regulatory circuits determine gene essentiality in cancer cells" available on [bioRxiv](). A corresponding R package including all source data required to run the code can be downloaded from [Figshare](https://figshare.com/s/33f68e70fbf6e6ac600f). The package can then be installed from the command line by typing 

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
