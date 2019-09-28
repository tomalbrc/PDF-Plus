require "preflight"

preflight = Preflight::Profiles::PDFA1A.new

puts preflight.check("/tmp/pdfplus.pdf").inspect

