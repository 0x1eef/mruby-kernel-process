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
      Kernel::Process.find_by(ppid)
    rescue Errno::ESRCH
      nil
    end

    ##
    # Alias
    alias_method :starts_at, :start_time

    ##
    # @return [String]
    def inspect
      "#<Kernel::Process:0x#{object_id.to_s(16)} " \
      "command=#{command} pid=#{pid} uid=#{uid}" \
      ">"
    end
    alias_method :to_s, :inspect
  end
end
