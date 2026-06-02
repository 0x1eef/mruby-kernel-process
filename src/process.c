/*
 * mruby-kernel-process — mruby bindings for BSD process APIs
 */

#include <mruby.h>
#include <mruby/error.h>
#include <mruby/data.h>
#include <mruby/class.h>
#include <mruby/array.h>

#include <sys/types.h>
#include <sys/user.h>
#include <libutil.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

void mrb_mruby_kernel_process_gem_init(mrb_state *mrb);
void mrb_mruby_kernel_process_gem_final(mrb_state *mrb);
static void proc_free(mrb_state *mrb, void *ptr);

static const
mrb_data_type proc_type = { "Kernel::Process", proc_free };

mrb_value
mrb_process_find(mrb_state *mrb, mrb_value self)
{
  mrb_int pid;
  struct kinfo_proc *proc;

  mrb_get_args(mrb, "i", &pid);
  proc = kinfo_getproc(pid);
  if (proc == NULL) {
    mrb_sys_fail(mrb, "kinfo_getproc");
  }
  return mrb_obj_value(
    Data_Wrap_Struct(mrb, mrb_class_ptr(self), &proc_type, proc)
  );
}

mrb_value
mrb_process_all(mrb_state *mrb, mrb_value self)
{
  int count;
  mrb_value mrb_procs;
  struct kinfo_proc *procs;

  mrb_procs = mrb_ary_new(mrb);
  procs = kinfo_getallproc(&count);
  if (procs == NULL) {
    mrb_sys_fail(mrb, "kinfo_getallproc");
  }
  for (int i = 0; i < count; i++) {
    struct kinfo_proc *proc;
    mrb_value mrb_proc;
    proc = malloc(sizeof(*proc));
    if (proc == NULL) {
      free(procs);
      mrb_sys_fail(mrb, "malloc");
    }
    memcpy(proc, &procs[i], sizeof(*proc));
    mrb_proc = mrb_obj_value(
      Data_Wrap_Struct(mrb, mrb_class_ptr(self), &proc_type, proc)
    );
    mrb_ary_push(mrb, mrb_procs, mrb_proc);
  }
  free(procs);
  return mrb_procs;
}

mrb_value
mrb_process_pid(mrb_state *mrb, mrb_value self)
{
  struct kinfo_proc *proc;
  pid_t pid;

  proc = DATA_PTR(self);
  pid = proc->ki_pid;
  return mrb_fixnum_value((mrb_int)pid);
}

mrb_value
mrb_process_ppid(mrb_state *mrb, mrb_value self)
{
  struct kinfo_proc *proc;
  pid_t ppid;

  proc = DATA_PTR(self);
  ppid = proc->ki_ppid;
  return mrb_fixnum_value((mrb_int)ppid);
}

mrb_value
mrb_process_pgid(mrb_state *mrb, mrb_value self)
{
  struct kinfo_proc *proc;
  pid_t pgid;

  proc = DATA_PTR(self);
  pgid = proc->ki_pgid;
  return mrb_fixnum_value((mrb_int)pgid);
}

mrb_value
mrb_process_sid(mrb_state *mrb, mrb_value self)
{
  struct kinfo_proc *proc;
  pid_t sid;

  proc = DATA_PTR(self);
  sid  = proc->ki_sid;
  return mrb_fixnum_value((mrb_int)sid);
}

mrb_value
mrb_process_tpgid(mrb_state *mrb, mrb_value self)
{
  struct kinfo_proc *proc;
  pid_t tpgid;

  proc = DATA_PTR(self);
  tpgid = proc->ki_tpgid;
  return mrb_fixnum_value((mrb_int)tpgid);
}

mrb_value
mrb_process_uid(mrb_state *mrb, mrb_value self)
{
  struct kinfo_proc *proc;
  uid_t uid;

  proc = DATA_PTR(self);
  uid = proc->ki_uid;
  return mrb_fixnum_value((mrb_int)uid);
}

mrb_value
mrb_process_ruid(mrb_state *mrb, mrb_value self)
{
  struct kinfo_proc *proc;
  uid_t ruid;

  proc = DATA_PTR(self);
  ruid = proc->ki_ruid;
  return mrb_fixnum_value((mrb_int)ruid);
}

mrb_value
mrb_process_svuid(mrb_state *mrb, mrb_value self)
{
  struct kinfo_proc *proc;
  uid_t svuid;

  proc = DATA_PTR(self);
  svuid = proc->ki_svuid;
  return mrb_fixnum_value((mrb_int)(svuid));
}

void
mrb_mruby_kernel_process_gem_init(mrb_state *mrb)
{
  struct RClass *cProcess;

  cProcess = mrb_define_class_under(mrb, mrb->kernel_module, "Process", mrb->object_class);

  mrb_define_singleton_method(mrb, cProcess, "all", mrb_process_all, MRB_ARGS_NONE());
  mrb_define_singleton_method(mrb, cProcess, "find", mrb_process_find, MRB_ARGS_REQ(1));

  mrb_define_method(mrb, cProcess, "pid", mrb_process_pid, MRB_ARGS_NONE());
  mrb_define_method(mrb, cProcess, "ppid", mrb_process_ppid, MRB_ARGS_NONE());
  mrb_define_method(mrb, cProcess, "pgid", mrb_process_pgid, MRB_ARGS_NONE());
  mrb_define_method(mrb, cProcess, "sid", mrb_process_sid, MRB_ARGS_NONE());
  mrb_define_method(mrb, cProcess, "tpgid", mrb_process_tpgid, MRB_ARGS_NONE());
  mrb_define_method(mrb, cProcess, "uid", mrb_process_uid, MRB_ARGS_NONE());
  mrb_define_method(mrb, cProcess, "ruid", mrb_process_ruid, MRB_ARGS_NONE());
  mrb_define_method(mrb, cProcess, "svuid", mrb_process_svuid, MRB_ARGS_NONE());

  MRB_SET_INSTANCE_TT(cProcess, MRB_TT_CDATA);
}

void
mrb_mruby_kernel_process_gem_final(mrb_state *mrb)
{
  (void)mrb;
}

static void
proc_free(mrb_state *mrb, void *ptr)
{
  free(ptr);
}
