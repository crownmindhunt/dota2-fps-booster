using System.Collections.ObjectModel;
using System.Windows.Input;

namespace Dota2FpsBooster.Shell.ViewModels;

public sealed class TweakListViewModel
{
    public ObservableCollection<TweakItem> Tweaks { get; } = new();
    public ICommand ApplySelectedCommand { get; }

    public TweakListViewModel()
    {
        ApplySelectedCommand = new RelayCommand(_ => ApplySelected());
        Tweaks.Add(new TweakItem("gpu.shader_cache_size", "Shader cache size", true));
        Tweaks.Add(new TweakItem("cpu.priority_high", "Raise process priority", false));
        Tweaks.Add(new TweakItem("timer.resolution_0_5ms", "0.5ms timer resolution", false));
    }

    private void ApplySelected()
    {
        foreach (var t in Tweaks)
            if (t.Selected) Native.ApplyTweak(t.Id);
    }
}

public sealed class TweakItem
{
    public string Id { get; }
    public string DisplayName { get; }
    public bool Selected { get; set; }
    public TweakItem(string id, string name, bool selected)
        => (Id, DisplayName, Selected) = (id, name, selected);
}