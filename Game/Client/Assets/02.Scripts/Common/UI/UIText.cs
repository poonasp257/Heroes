using UnityEngine;
using UnityEngine.UI;

namespace Heroes {
	public class UIText : Text {
		[SerializeField] private bool enableWordWrap = false;

		protected override void Start() {
			base.Start();

			if(!enableWordWrap) {
				base.text = base.text.Replace(' ', '\u00A0');
			}
		}

		public override string text {
			get => base.text;
			set {
				if (enableWordWrap) {
					base.text = value;
					return;
				}

				base.text = value.Replace(' ', '\u00A0');
			}
		}
	}
}