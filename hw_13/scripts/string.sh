#!/bin/bash
#SBATCH --job-name=stringtie
#SBATCH --output=stringtie.out
#SBATCH --error=stringtie.err
#SBATCH --time=01:00:00
#SBATCH --cpus-per-task=4
#SBATCH --mem=16G


mkdir -p stringtie_output

stringtie star_output/RNA_Aligned.sortedByCoord.out.bam \
	    -o stringtie_output/sample.gtf \
	        -p 4 \
		    -G /projects/mipt_dbmp_biotechnology/GRCh38/Homo_sapiens.GRCh38.110.chr.gtf
