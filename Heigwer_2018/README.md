# Time-resolved mapping of genetic interactions to model signaling pathway vulnerabilities

The paper that this repository is currently under submission

## Abstract

Context-dependent changes in genetic vulnerabilities are important to understand the wiring of cellular pathways and variations in different environmental conditions. Genetic interaction mapping has expanded our principal knowledge of cellular networks. However, frameworks to investigate the plasticity of genetic networks over time or in response to external stresses are lacking. To analyze the plasticity of genetic interactions within regulatory networks, we performed an arrayed combinatorial RNAi screen in Drosophila cells over time and under perturbation of Ras signaling activity. Using an image-based morphology assay to capture broad cellular phenotypes, we assessed the effect of 12768 pairwise RNAi perturbations at three time points and after pharmacological MEK inhibition. We found that genetic interactions form in different trajectories and developed a model (MODIFI) to analyze how pathways rewire. MODIFI provided overall greater power to identify and characterize differential interactions. We further identified an unexpected interaction between Ras (KRAS) and Rel (NF-kB) which depends on the Ras-signaling status.

## Supporting analysis code for the manuscript

This directory contains an R package that can reproduce the figures in the manuscript. The package can be downloaded from the GitHub repository by clicking on the package file ('Modifi_0.1.0.tar.gz') and then clicking the 'Download' button on the right. The package can then be installed from the command line by typing 

```{sh}
R CMD INSTALL CGIMhd17_0_1_0.tar.gz
```

or using for example [Rstudio](https://www.rstudio.com/). Once the package is installed you can view the package vignette describing the analysis in R.

```{r}
library(Modifi)
vignette('MODIFI_analysis')
```

## Contact

Should you encounter any issues or have any questions please contact Florian Heigwer <f.heigwer@dkfz.de>.
