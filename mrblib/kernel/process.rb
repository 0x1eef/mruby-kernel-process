module Kernel
  class Process
    extend Enumerable
    ##
    # @return [Array<Kernel::Process>]
    def self.each(...)
      all.each(...)
    end

    ##
    # Alias
    alias_method :starts_at, :start_time
  end
end
