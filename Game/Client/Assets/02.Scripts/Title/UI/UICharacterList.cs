using System;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

namespace Heroes {
    public class UICharacterList : MonoBehaviour {
        private List<UICharacterBox> characterBoxList = new List<UICharacterBox>();

        [Header("Character Count")]
        [SerializeField] private Text charactersCountUI;

        [Header("Character Box Prefab")]
        [SerializeField] private GameObject characterBoxPrefab;
        [SerializeField] private GameObject creatableBoxPrefab;
        [SerializeField] private GameObject lockedBoxPrefab;

        [Header("Button")]
        [SerializeField] private UIButton changePostionButton;

        public int CreatableCharactersCount { get; set; }

        private void Start() {
            changePostionButton.onClick.AddListener(this.turnOnOffChangeCharacterBoxesPostionMode);
        }

        private void Update() {
            charactersCountUI.text = string.Format("({0}/{1})",
                characterBoxList.Count, CreatableCharactersCount);
        }

        private void turnOnOffChangeCharacterBoxesPostionMode() {
            foreach(var characterBox in characterBoxList) {
                characterBox.ChangePositionMode = !characterBox.ChangePositionMode;
            }
        }

        public void initialize(List<CharacterInfo> characterList) {
            foreach(var characterInfo in characterList) {
                var characterBoxObj = Instantiate(characterBoxPrefab, this.transform);
                var characterBox = characterBoxObj.GetComponent<UICharacterBox>();
                characterBox.initialize(characterInfo, characterList.Count);
                characterBoxList.Add(characterBox);
            }

            if (CreatableCharactersCount == characterList.Count) return;

            Instantiate(creatableBoxPrefab, this.transform);
            int remainEmptyBoxCount = CreatableCharactersCount - characterList.Count - 1;
            for(int i = 0; i < remainEmptyBoxCount; ++i) { 
                Instantiate(lockedBoxPrefab, this.transform);
            }
        }

        public void changeCharacterOrder(int fromIndex, int toIndex) {
            var from = this.transform.GetChild(fromIndex);
            from.SetSiblingIndex(toIndex);
        }
    }
}