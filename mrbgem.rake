load File.join(__dir__, "mrblib", "kernel", "process", "version.rb")

MRuby::Gem::Specification.new('mruby-kernel-process') do |spec|
  spec.license = '0BSD'
  spec.author  = '0x1eef'
  spec.summary = 'mruby bindings for BSD process APIs'

  if ENV["BUILD"] == "test"
    spec.add_dependency 'mruby-minitest', github: "0x1eef/mruby-minitest", branch: "main"
    spec.add_dependency 'mruby-process', github: '0x1eef/mruby-process', branch: "main"
  end

  spec.cc.flags << '-Wall'
  spec.cc.flags << '-Wpedantic'
  spec.linker.flags << '-lutil'
end
