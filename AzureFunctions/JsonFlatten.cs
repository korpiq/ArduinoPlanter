using System.Collections.Generic;
using System.Net;
using System.Net.Http;
using System.Threading.Tasks;
using Microsoft.Azure.WebJobs;
using Microsoft.Azure.WebJobs.Extensions.Http;
using Microsoft.Azure.WebJobs.Host;
using Newtonsoft.Json;

namespace AzureFunctions
{
    public static class JsonFlatten
    {
        [FunctionName("JsonFlatten")]
        public static async Task<HttpResponseMessage> Run([HttpTrigger(AuthorizationLevel.Anonymous, "post", Route = null)]HttpRequestMessage req, TraceWriter log)
        {
            string postContent = await req.Content.ReadAsAsync<string>();

            Dictionary<string, object> deepInput =
                JsonConvert.DeserializeObject<Dictionary<string, object>>(postContent);
            Dictionary<string, object> flatOutput = new Dictionary<string, object>();

            Flatten(deepInput, flatOutput, "", "_");

            string flatJson = JsonConvert.SerializeObject(flatOutput);

            return req.CreateResponse(HttpStatusCode.OK, flatJson);
        }

        private static void Flatten(Dictionary<string, object> deepInput, Dictionary<string, object> flatOutput, string prefix, string separator)
        {
            foreach(var key in deepInput.Keys) {
                var value = deepInput[key];
                if (value is Dictionary<string, object>)
                {
                    Flatten(value as Dictionary<string, object>, flatOutput, prefix + key + separator, separator);
                }
                else
                {
                    flatOutput[prefix + key] = value;
                }
            }
        }
    }
}
