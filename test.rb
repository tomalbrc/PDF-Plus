require "preflight"

preflight = Preflight::Profiles::PDFX1A.new

puts preflight.check("/tmp/MyRanda.pdf").inspect

File.open("somefile.pdf", "rb") do |file|
  puts preflight.check(file).inspect
end

