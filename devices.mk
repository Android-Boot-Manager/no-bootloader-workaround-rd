# use custom commands...
rd-generic: rd-device
	@cat utils/env-fallback.sh >> out/rd/env.sh

# ...or just the default (pro tip: you can also append commands to that target)
# rd-yggdrasil: rd-default
# This is commented out because the build system auto-generates  the default target
