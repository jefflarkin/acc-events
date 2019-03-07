#include <stdio.h>
#include <acc_prof.h>
#define bufsize 1024

void oaccToolRegister(acc_prof_info  *profinfo,
                      acc_event_info *eventinfo,
                      acc_api_info   *apiinfo)
{
  char funcname[bufsize], varname[bufsize];

  switch(profinfo->event_type)
  {
    case acc_ev_enqueue_upload_start  :
    case acc_ev_enqueue_upload_end    :
    case acc_ev_enqueue_download_start:
    case acc_ev_enqueue_download_end  :
    {
      acc_data_event_info *dataevent = (acc_data_event_info*) eventinfo;
      switch(dataevent->parent_construct)
      {
        case acc_construct_parallel:
        case acc_construct_serial:
        case acc_construct_kernels:
        case acc_construct_loop:
        case acc_construct_data: // WAR - Want to remove this to focus on compute constructs
          if ( dataevent->implicit )
            fprintf(stderr, "Implicit data copy of %s for %d bytes in %s at line number %d\n", 
                            dataevent->var_name, dataevent->valid_bytes, 
                            profinfo->func_name, profinfo->line_no);
          else
            fprintf(stderr, "Explicit data copy of %s for %d bytes in %s at line number %d\n", 
                            dataevent->var_name, dataevent->valid_bytes, 
                            profinfo->func_name, profinfo->line_no);
          break;
        default:
          fprintf(stderr, "UNKNOWN: %d\n", dataevent->parent_construct);
      }
    }
  }
}
typedef void (*regroutine)( acc_event_t, acc_prof_callback_t, int );
void acc_register_library(acc_prof_reg regFunc, acc_prof_reg unregFunc, acc_prof_lookup lookup)
{
  regFunc(acc_ev_enqueue_upload_start  , oaccToolRegister, 0);
  regFunc(acc_ev_enqueue_upload_end    , oaccToolRegister, 0);
  regFunc(acc_ev_enqueue_download_start, oaccToolRegister, 0);
  regFunc(acc_ev_enqueue_download_end  , oaccToolRegister, 0);
}
