module BSD
  class Process
    extend Enumerable
    ##
    # @return [Array<BSD::Process>]
    def self.each(...)
      all.each(...)
    end
  end
end
