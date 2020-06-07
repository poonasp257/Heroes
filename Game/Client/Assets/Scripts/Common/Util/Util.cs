using System.IO;
using System.Text;
using System.Threading.Tasks;

namespace Heroes {
	public class Util {
		public static void swap<T>(ref T lhs, ref T rhs) {
			T temp = lhs;
			lhs = rhs;
			rhs = temp;
		}
	
		public static async Task CreateJsonFile(string path, string fileName, string jsonData) {
			var fileStream = new FileStream(string.Format("{0}/{1}.json", path, fileName), FileMode.Create);
			byte[] data = Encoding.UTF8.GetBytes(jsonData);
			await fileStream.WriteAsync(data, 0, data.Length);
			fileStream.Close();
		}

		public static async Task<string> LoadJsonFile(string path, string fileName) {
			var fileStream = new FileStream(string.Format("{0}/{1}.json", path, fileName), FileMode.Open);
			byte[] data = new byte[fileStream.Length];
			await fileStream.ReadAsync(data, 0, data.Length);
			fileStream.Close();
			return Encoding.UTF8.GetString(data);
		}
	}
}