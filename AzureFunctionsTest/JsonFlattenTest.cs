using AzureFunctions;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Collections.Generic;

namespace AzureFunctions
{
    [TestClass]
    public class TestJsonFlatten
    {
        PrivateType privateTypeJsonClass = new PrivateType(typeof(JsonFlatten));

        [TestMethod]
        public void TestFlattenDeeplyNestedJsonOk()
        {
            Dictionary<string, object>
                deepInput = new Dictionary<string, object>(),
                secondLevelObject = new Dictionary<string, object>(),
                thirdLevelObject = new Dictionary<string, object>(),
                expected = new Dictionary<string, object>(),
                actual = new Dictionary<string, object>();

            string
                topLevelScalar = "top level trivial value",
                secondLevelScalar = "second level trivial value",
                thirdLevelScalar = "third level trivial value";

            thirdLevelObject["thirdLevelScalar"] = thirdLevelScalar;
            secondLevelObject["thirdLevelObject"] = thirdLevelObject;
            secondLevelObject["secondLevelScalar"] = secondLevelScalar;
            deepInput["secondLevelObject"] = secondLevelObject;
            deepInput["topLevelScalar"] = topLevelScalar;

            expected["topLevelScalar"] = topLevelScalar;
            expected["secondLevelObject_secondLevelScalar"] = secondLevelScalar;
            expected["secondLevelObject_thirdLevelObject_thirdLevelScalar"] = thirdLevelScalar;

            object[] parameters = { deepInput, actual, "", "_" };
            privateTypeJsonClass.InvokeStatic("Flatten", parameters);

            CollectionAssert.AreEquivalent(expected, actual);
        }
    }
}
