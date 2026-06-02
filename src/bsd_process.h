#ifndef MRUBY_BSD_PROCESS_H
#define MRUBY_BSD_PROCESS_H

#include <mruby.h>
#include <mruby/error.h>
#include <mruby/data.h>
#include <mruby/class.h>
#include <mruby/array.h>

void mrb_mruby_bsd_process_gem_init(mrb_state *mrb);
void mrb_mruby_bsd_process_gem_final(mrb_state *mrb);

#endif /* MRUBY_BSD_PROCESS_H */
