#include "src/utils/FieldsJSON.h"

namespace FieldsJSON {

	static JSONVar getField(JSONVar& doc, const char* key) {
		return doc[String(key)];
	}

	static bool isNumberType(const JSONVar& value) {
		const auto valueType = (JSON.typeof)(value);
		return valueType == "number" || valueType == "integer";
	}

	bool isUndefined(const JSONVar& value) {
		return (JSON.typeof)(value) == "undefined";
	}

	bool hasNonEmptyString(JSONVar& doc, const char* key) {
		const JSONVar value = getField(doc, key);

		if ((JSON.typeof)(value) != "string") {
			return false;
		}

		const char* str = value;
		return str != nullptr && str[0] != '\0';
	}

	bool hasNonEmptyNumber(JSONVar& doc, const char* key) {
		const JSONVar value = getField(doc, key);

		if (!isNumberType(value)) {
			return false;
		}

		const int number = static_cast<int>(value);
		return number > 0 && number <= 65535;
	}

} // namespace FieldsJSON
