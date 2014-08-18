<?xml version="1.0" encoding="UTF-8" ?>
<Package name="emotional-framework-installer" format_version="4">
    <Manifest src="manifest.xml" />
    <BehaviorDescriptions>
        <BehaviorDescription name="behavior" src="installer" xar="behavior.xar" />
    </BehaviorDescriptions>
    <Dialogs />
    <Resources>
        <File name="libnao-emotional-framework" src="installer/native/lib/libnao-emotional-framework.so" />
        <File name="choice_sentences" src="installer/Aldebaran/choice_sentences.xml" />
    </Resources>
    <Topics />
    <IgnoredPaths />
</Package>
