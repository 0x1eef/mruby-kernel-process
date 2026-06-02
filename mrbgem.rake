MRuby::Gem::Specification.new('mruby-bsd-process') do |spec|
  spec.license = '0BSD'
  spec.author  = '0x1eef'
  spec.summary = 'mruby bindings for BSD process APIs'
  spec.rbfiles.concat Dir["mrblib/bsd.rb", "mrblib/**/*.rb"]
    .map { File.expand_path __dir__, _1 }
    .select { File.file?(_1) }

  if ENV["BUILD"] == "TEST"
    spec.add_dependency 'mruby-minitest', github: "0x1eef/mruby-minitest", branch: "main"
    spec.add_dependency 'mruby-process', github: '0x1eef/mruby-process', branch: "main"
  end
  spec.cc.flags << '-Wall'
  spec.cc.flags << '-Wpedantic'
  spec.linker.flags << '-lutil'
end
