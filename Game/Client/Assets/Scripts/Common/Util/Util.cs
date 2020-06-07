using System.IO;
using System.Text;
using System.Diagnostics;
using System.Threading.Tasks;
using UnityEngine;

using Debug = UnityEngine.Debug;
using System;

namespace Heroes {
	public class Util {
		public static void Swap<T>(ref T lhs, ref T rhs) {
			T temp = lhs;
			lhs = rhs;
			rhs = temp;
		}

		public static void MeasureExecutionTime(string name, Action asyncFunc) {
			Stopwatch timer = Stopwatch.StartNew();
			Debug.Log(string.Format("{0} started...", name));

			asyncFunc?.Invoke();

			timer.Stop();
			float endTime = timer.ElapsedMilliseconds * 0.001f;
			Debug.Log(string.Format("{0} finished: {1:0.000}s", name, endTime));
		}

		public static void MeasureExecutionTime(string name, Func<Task> asyncFunc) {
			Stopwatch timer = Stopwatch.StartNew();
			Debug.Log(string.Format("{0} started...", name));

			asyncFunc?.Invoke();

			timer.Stop();
			float endTime = timer.ElapsedMilliseconds * 0.001f;
			Debug.Log(string.Format("{0} finished: {1:0.000}s", name, endTime));
		}

		public static void CreateJsonFile(string directory, string fileName, string jsonData) {
			string path = Application.streamingAssetsPath + string.Format("{0}/{1}.json", directory, fileName);
			var streamWriter = new StreamWriter(path);
			streamWriter.Write(jsonData);
		}

		public static string LoadJsonFile(string directory, string fileName) {
			string path = Application.streamingAssetsPath + string.Format("{0}/{1}.json", directory, fileName);
			var streamReader = new StreamReader(path);
			var jsonData = streamReader.ReadToEnd();
			return jsonData;
		}

		public static async Task AsyncCreateJsonFile(string directory, string fileName, string jsonData) {
			string path = Application.streamingAssetsPath + string.Format("{0}/{1}.json", directory, fileName);
			using (StreamWriter writer = new StreamWriter(path)) {
				await writer.WriteAsync(jsonData);
            }		
		}

		public static async Task<string> AsyncLoadJsonFile(string directory, string fileName) {
			string path = Application.streamingAssetsPath + string.Format("{0}/{1}.json", directory, fileName);
			using(StreamReader reader = new StreamReader(path)) {
				var jsonData = await reader.ReadToEndAsync();
				return jsonData;
			}
		}
	}
}