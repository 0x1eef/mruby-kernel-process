module Kernel
  class Process
    extend Enumerable
    ##
    # @return [Array<Kernel::Process>]
    def self.each(...)
      all.each(...)
    end

    ##
    # Returns the parent as a {Kernel::Process Kernel::Process} object.
    # @return [Kernel::Process, nil]
    def parent
      Kernel::Process.find(ppid)
    rescue Errno::ESRCH
      nil
    end

    ##
    # Alias
    alias_method :starts_at, :start_time
  end
end
