#!/bin/bash
#SBATCH --job-name=fastp
#SBATCH --output=fastp.out
#SBATCH --error=fastp.err
#SBATCH --time=01:00:00
#SBATCH --cpus-per-task=4
#SBATCH --mem=8G

mkdir trimmed
fastp -i Erik_mat_CD4_MiLab_S52_R1_001.fastq.gz -I Erik_mat_CD4_MiLab_S52_R2_001.fastq.gz -o Erik_mat_CD4_MiLab_S52_R1_001_trimmed.fastq.gz -O Erik_mat_CD4_MiLab_S52_R2_001_trimmed.fastq.gz -w 4 --detect_adapter_for_pe --html fastp_report.html

mkdir -p fastqc/fastqc_trimmed
fastqc -t 4 -o fastqc/fastqc_trimmed Erik_mat_CD4_MiLab_S52_R1_001_trimmed.fastq.gz Erik_mat_CD4_MiLab_S52_R2_001_trimmed.fastq.gz

cd fastqc/fastqc_trimmed
multiqc .
