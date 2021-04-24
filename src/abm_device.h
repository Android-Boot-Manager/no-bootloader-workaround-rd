#ifndef ABM_DEVICEH
#define ABM_DEVICEH
//TODO: remove this, instead use constants
struct abm_device {
   int  dpi;
   int x_res;
   int y_res;
   char * touchscreen_dev_path;
   char * codname;
   char * sd_card_meta_path;
};  
#endif
