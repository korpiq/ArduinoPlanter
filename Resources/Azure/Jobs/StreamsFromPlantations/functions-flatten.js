function main(deepObject) {

    function flatten(deepObject, flattenedObject, prefix, separator) {

        for(var key in deepObject) {
            var value = deepObject[key];
            if (typeof(value) === 'object') {
                flatten(value, flattenedObject, prefix + key + separator, separator);
            } else {
                flattenedObject[prefix + key] = value;
            }
        }

        return flattenedObject;
    }

    return flatten(deepObject, {}, '', '_');
}
