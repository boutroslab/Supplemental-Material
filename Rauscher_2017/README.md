# Towards an Integrated Map of Genetic Interactions in Cancer Cells
## Supporting analysis code for the manuscript

This directory contains an R package that can reproduce the figures in the manuscript. The package can be downloaded manually or by cloning the GitHub repository. The package can then be installed using 

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
