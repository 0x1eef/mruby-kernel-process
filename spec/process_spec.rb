describe "Kernel::Process" do
  describe ".self" do
    subject { Kernel::Process.self }

    it "returns an instance of Kernel::Process" do
      expect(subject.class).must_equal  Kernel::Process
    end

    it "returns the pid" do
      expect(subject.pid).must_equal Process.pid
    end

    it "returns the parent pid" do
      expect(subject.ppid).must_equal Process.ppid
    end

    it "returns the uid" do
      expect(subject.uid).must_equal Process.uid
    end

    it "returns the command name" do
      expect(subject.command).must_equal "mruby"
    end
  end
end

Minitest.run(ARGV) || exit(1)
