module Kernel
  class Process
    extend Enumerable
    ##
    # @return [Array<Kernel::Process>]
    def self.each(...)
      all.each(...)
    end
  end
end
