# MEK inhibition activates Wnt signalling and induces stem cell plasticity in colorectal cancer organoids

This repository corresponds to the article [MEK inhibition activates Wnt signalling and induces stem cell plasticity in colorectal cancer organoids](https://www.nature.com/articles/s41467-019-09898-0) by Zhan, Ambrosi, Wandmacher _et al._.

## Supporting analysis code for the manuscript

This directory contains an R package that can reproduce the figures in the manuscript. The package can be downloaded from the GitHub repository by clicking on the package file ('MEKWnt2018.tar.gz') and then clicking the 'Download' button on the right. The package can then be installed from the command line by typing 

```{sh}
R CMD INSTALL MEKWnt2018_0_1_0.tar.gz
```

or using for example [Rstudio](https://www.rstudio.com/). Once the package is installed you can view the package vignette describing the analysis in R.

```{r}
library(MEKWnt2018)
browseVignettes('MEKWnt2018')
```

## Contact

Should you encounter any issues or have any questions please contact Benedikt Rauscher <b.rauscher@dkfz.de>.
