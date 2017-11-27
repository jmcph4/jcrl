cd ..
wc -l src/* | sort -r | grep total | awk '($1=$1);1' | cut -d " " -f1 | uniq
