using System.Threading.Tasks;

namespace Heroes {
    public class MonsterStateManager : CharacterStateManager {
        public MonsterInfo info;

        public async void die() {
            this.executeAction(ActionType.Die);
            await Task.Delay(3000);
            this.gameObject.SetActive(false);
        }
    }
}