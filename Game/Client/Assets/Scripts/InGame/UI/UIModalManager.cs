using System.Linq;
using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
    public class UIModalManager : MonoBehaviour {
        private LinkedList<GameObject> modalStack = new LinkedList<GameObject>();

        [SerializeField] private GameObject logoutModal = null;
        [SerializeField] private GameObject statusModal = null;
        [SerializeField] private GameObject skillModal = null;
        [SerializeField] private GameObject inventoryModal = null;

        public static bool EnabledInput { get; set; }

        private void Start() {
            EnabledInput = true;
        }

        private void Update() {
            if (!EnabledInput) return;

            if (Input.GetButtonDown("Cancel")) {
                if(modalStack.Count == 0) {
                    this.enableModal(logoutModal);
                    return;
                }

                this.disableOnTopModal();
            }

            if (Input.GetButtonDown("Status")) {
                if (statusModal.activeSelf) {
                    this.disableModal(statusModal);
                    return;
                }

                this.enableModal(statusModal);
            }

            if (Input.GetButtonDown("Skill")) {
                if (skillModal.activeSelf) {
                    this.disableModal(skillModal);
                    return;
                }

                this.enableModal(skillModal);
            }

            if (Input.GetButtonDown("Inventory")) {
                if (inventoryModal.activeSelf) {
                    this.disableModal(inventoryModal);
                    return;
                }

                this.enableModal(inventoryModal);
            }
        }

        private void disableOnTopModal() {
            var modal = modalStack.Last();
            modal.SetActive(false);
            modalStack.RemoveLast();
        }

        private void disableModal(GameObject enableModal) {
            var node = modalStack.First;
            while (node != null) {
                var nextNode = node.Next;
                var modal = node.Value;
                if (modal == enableModal) {
                    modal.SetActive(false);
                    modalStack.Remove(node);
                    return;
                }

                node = nextNode;
            }
        }

        private void enableModal(GameObject disabledModal) {
            disabledModal.SetActive(true);
            modalStack.AddLast(disabledModal);
        }        
    }
}