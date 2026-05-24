#pragma once

#include <Arduino_JSON.h>
#include <cstdint>

namespace FieldsJSON {

	bool isUndefined(const JSONVar& value);
	bool hasNonEmptyString(JSONVar& doc, const char* key);
	bool hasNonEmptyNumber(JSONVar& doc, const char* key);

} // namespace FieldsJSON
