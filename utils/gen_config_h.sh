. $1
touch $2
$GEN_HEADER || exit 0
# Header
echo "#ifndef DEVICE_CONFIG_H" >> $2
echo "#define DEVICE_CONFIG_H" >> $2
# Variables
echo "#define DPI $DEVICE_DPI" >> $2
echo "#define CODENAME \"$DEVICECODENAME\"" >> $2
echo "#define SD_META_PATH \"$SD_META_PATH\"" >> $2
echo "#define TOUCHSCREEN_PATH \"$TOUCHSCREEN_PATH\"" >> $2
echo "#define SYSTEMPART \"$SYSTEMPART\"" >> $2
echo "#define VENDORPART \"$VENDORPART\"" >> $2
# Footer
echo "#endif" >> $2
