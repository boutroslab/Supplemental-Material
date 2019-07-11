# Detection of mutational patterns in cell free DNA (cfDNA) of colorectal cancer by custom amplicon sequencing

The paper this repository relates to is available on the [Molecular Oncology journal website](https://febs.onlinelibrary.wiley.com/doi/abs/10.1002/1878-0261.12539).

## Abstract

Monitoring the mutational patterns of solid tumors during cancer therapy is a major challenge in oncology. Analysis of mutations in cell free (cf) DNA offers a non‐invasive approach to detect mutations that may be prognostic for disease survival or predictive for primary or secondary drug resistance. A main challenge for the application of cfDNA as a diagnostic tool is the diverse mutational landscape of cancer. Here, we developed a flexible end‐to‐end experimental and bioinformatics workflow to analyze mutations in cfDNA using custom amplicon sequencing. Our approach relies on open software tools to select primers suitable for multiplex PCR using minimal cfDNA as input. In addition, we developed a robust linear model to identify specific genetic alterations from sequencing data of cfDNA. We used our workflow to design a custom amplicon panel suitable for detection of hotspot mutations relevant for colorectal cancer and analyzed mutations in serial cfDNA samples from a pilot cohort of 34 patients with advanced colorectal cancer. Using our method, we could detect recurrent and patient‐specific mutational patterns in the majority of patients. Furthermore, we show that dynamic changes of mutant allele frequencies in cfDNA correlate well with disease progression. Finally, we demonstrate that sequencing of cfDNA can reveal mechanisms of resistance to anti‐EGFR antibody treatment. Thus, our approach offers a simple and highly customizable method to explore genetic alterations in cfDNA.

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
