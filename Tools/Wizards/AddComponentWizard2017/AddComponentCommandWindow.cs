using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace AddComponentWizard2017
{
	public enum AddComponentCommandType
	{
		Component,
		ServerObject,
		PlayerState,
		BotState,
		Anchor,
		Path,
		Volume,
		EffectLayer,
		AnimationEvent,
		Config,
	}

	public partial class AddComponentCommandWindow : Form
	{
		public AddComponentCommandWindow(string path)
		{
			InitializeComponent();

			addComponentTab.SetInitialPath(this, path);
			addServerObjectTab.SetInitialPath(this, path);
			addPlayerStateTab.SetInitialPath(this, path);
			addBotStateTab.SetInitialPath(this, path);
			addAnchorTab.SetInitialPath(this, path);
			addPathTab.SetInitialPath(this, path);
			addVolumeTab.SetInitialPath(this, path);
			addEffectLayerTab.SetInitialPath(this, path);
			addAnimationEventTab.SetInitialPath(this, path);
			addConfigTab.SetInitialPath(this, path);
		}

		public AddComponentCommandType Type { get; set; }
		public AddComponentTab AddComponent { get { return addComponentTab; } }
		public AddServerObjectTab AddServerObject { get { return addServerObjectTab; } }
		public AddPlayerStateTab AddPlayerState { get { return addPlayerStateTab; } }
		public AddBotStateTab AddBotState { get { return addBotStateTab; } }
		public AddAnchorTab AddAnchor { get { return addAnchorTab; } }
		public AddPathTab AddPath { get { return addPathTab; } }
		public AddVolumeTab AddVolume { get { return addVolumeTab; } }
		public AddEffectLayerTab AddEffectLayer { get { return addEffectLayerTab; } }
		public AddAnimationEventTab AddAnimationEvent { get { return addAnimationEventTab; } }
		public AddConfigTab AddConfig { get { return addConfigTab; } }
	}
}
