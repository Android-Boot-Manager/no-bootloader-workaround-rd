#!/bin/sh

if [ -f "env.sh" ]; then
    . /env.sh
else 
    . /env-fallback.sh
fi

if [ $# -eq 0 ]; then
    #No arguments provided, so we must boot from real system partition
    #FIXME: A/B handling  
    mkdir /system
    mount $SYSTEMPART /system
    mount $VENDORPART /system/vendor
    exec switch_root /system /init
fi
