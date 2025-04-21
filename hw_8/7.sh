#!/bin/bash

awk '
BEGIN {
    max_ins_len = 0
        max_del_len = 0
	    ins_chr = ""
	        del_chr = ""
	}
{
	    if ($0 ~ /^#/) next 
		        
		        chr = $1
			    len_ref = length($4)
			        len_alt = length($5)
				    
				    if (len_alt > len_ref) {
					            ins_len = len_alt - len_ref
						            if (ins_len > max_ins_len) {
								                max_ins_len = ins_len
										            ins_seq = substr($5, len_ref + 1)
											                ins_chr = chr
													        }
													    }
												        
												     
												        if (len_ref > len_alt) {
														        del_len = len_ref - len_alt
															        if (del_len > max_del_len && chr != ins_chr) {  
																	            max_del_len = del_len
																		                del_seq = substr($4, len_alt + 1)
																				            del_chr = chr
																					            }
																					        }
																				}
																			END {
																			    print "Longest insertion in chromosome " ins_chr ":" > "fout"
																			        print ins_seq >> "fout"
																				    print "" >> "fout"
																				        print "Longest deletion in chromosome " del_chr ":" >> "fout"
																					    print del_seq >> "fout"
																				    }' hw_8/clinvar_20250330.vcf
