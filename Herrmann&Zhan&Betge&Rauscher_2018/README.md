# Detection of mutational patterns in cell free DNA (cfDNA) of colorectal cancer by custom amplicon sequencing

The paper this repository relates to is currently under revision.

## Supporting computer code 

This directory contains an R package which includes markdown files and data to reproduce the figures of the manuscript. The package can be downloaded by clicking on 'HDLB2018_0.1.0.tar.gz' followed by a click on 'Download'. It can then be installed by typing 

```{sh}
R CMD INSTALL CGIMhd17_0_1_0.tar.gz
```

on the command line or using for example [Rstudio](https://www.rstudio.com/). Once the package is installed you can view the package vignette describing the analysis in R:

```{r}
library(HDLB2018)
browseVignettes('HDLB2018')
```

## Contact

Should encounter any issues or have any question please contact Benedikt Rauscher (b.rauscher@dkfz.de)
