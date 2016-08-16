# Questo è un makefile predefinito da posizionare nella directory src di un repo
# Per funzionare necessita di:
# * https://github.com/matteoalessiocarrara/build-tools


DOC_DIR = ../doc
CHANGELOG_FILE = $(DOC_DIR)/CHANGELOG.md


changelog:
	mkdir --parents $(DOC_DIR)
	git changelog > $(CHANGELOG_FILE)