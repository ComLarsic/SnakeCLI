.PHONY: clean All

All:
	@echo "----------Building project:[ Snake - Debug ]----------"
	@cd "Snake" && "$(MAKE)" -f  "Snake.mk"
clean:
	@echo "----------Cleaning project:[ Snake - Debug ]----------"
	@cd "Snake" && "$(MAKE)" -f  "Snake.mk" clean
