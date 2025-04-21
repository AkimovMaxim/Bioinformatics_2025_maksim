#!/bin/bash

awk '
{
	  lower_line = tolower($0)
	    if (lower_line ~ /[0-9]/ && lower_line !~ /[xy]/) {
		        gsub(/\r?\n?$/, "", $0)
			    cnt = 0
			        for (i = 1; i <= length($0); i++) {
					      c = substr($0, i, 1)
					      if ("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-.,:;" ~ c) {
							            cnt++
								          }
								      }
							          total += cnt
								    }
						    }
					    END { print total }
					    ' hw8/6/6.1/fin > stdout
