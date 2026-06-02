module BSD::Process::Test
  extend self

  def self.root?
    Process.euid == 0
  rescue
    false
  end
end
