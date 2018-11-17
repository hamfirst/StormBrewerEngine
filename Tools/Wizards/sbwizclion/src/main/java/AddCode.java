import com.intellij.execution.ExecutionException;
import com.intellij.execution.configurations.GeneralCommandLine;
import com.intellij.execution.process.OSProcessHandler;
import com.intellij.execution.process.ProcessHandler;
import com.intellij.openapi.actionSystem.*;
import com.intellij.openapi.editor.Editor;
import com.intellij.openapi.project.Project;
import com.intellij.openapi.ui.InputValidator;
import com.intellij.openapi.ui.Messages;
import com.intellij.openapi.ui.NonEmptyInputValidator;
import com.intellij.openapi.ui.popup.*;
import com.intellij.pom.Navigatable;
import com.intellij.psi.PsiDirectory;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import javax.swing.*;
import java.nio.charset.Charset;
import java.util.ArrayList;
import java.util.List;
import java.util.Arrays;

class IdentifierNameValidator implements  InputValidator {
    @Override
    public boolean checkInput(String inputString) {
        if(inputString.isEmpty())
        {
            return false;
        }

        if(inputString.charAt(0) >= '0' && inputString.charAt(0) <= '9')
        {
            return false;
        }

        for(int index = 0; index < inputString.length(); ++index)
        {
            if(inputString.charAt(0) == '_' ||
                    (inputString.charAt(index) >= 'a' && inputString.charAt(index) <= 'z') ||
                    (inputString.charAt(index) >= 'A' && inputString.charAt(index) <= 'Z') ||
                    (inputString.charAt(index) >= '0' && inputString.charAt(index) <= '9'))
            {
                continue;
            }

            return false;
        }

        return true;
    }

    @Override
    public boolean canClose(final String inputString) {

        return checkInput(inputString);
    }
}



class NamePopup implements Runnable
{
    Project _project;
    String _selectedType;
    String _directory;

    public NamePopup(Project project, String selectedType, String directory)
    {
        _project = project;
        _selectedType = selectedType;
        _directory = directory;
    }

    @Override
    public void run() {
        String className = Messages.showInputDialog(
                "ClassName",
                "Enter Class Name",
                Messages.getQuestionIcon(),
                _selectedType,
                new IdentifierNameValidator());

        if(className == null || className.length() == 0)
        {
            return;
        }

        String rootdir = _project.getBaseDir().getCanonicalPath();
        ArrayList<String> command = new ArrayList<>();
        command.add(rootdir + "/addcode");
        command.add(_selectedType);
        command.add(className);
        command.add(_directory);
        command.add(rootdir);

        if(_selectedType != "Class")
        {
            command.add("m");
        }

        GeneralCommandLine generalCommandLine = new GeneralCommandLine(command);
        generalCommandLine.setCharset(Charset.forName("UTF-8"));
        generalCommandLine.setWorkDirectory(rootdir);

        ProcessHandler processHandler = null;
        try {
            processHandler = new OSProcessHandler(generalCommandLine);
            processHandler.startNotify();
        } catch (ExecutionException e) {
            e.printStackTrace();
        }
    }
}

class TemplateList implements ListPopupStep<String>
{
    Project _project;
    String _directory;
    String _selectedType;

    public TemplateList(Project project, String directory)
    {
        _project = project;
        _directory = directory;
    }

    @NotNull
    @Override
    public List getValues() {
        String[] templates = new String[]
                {
                        "Class",
                        "Refl",
                        "ReflCpp",
                        "Component",
                        "ServerObject",
                        "PlayerState",
                        "BotState",
                        "Config",
                        "EffectLayer",
                        "Anchor",
                        "Path",
                        "Volume"
                };

        return Arrays.asList(templates);
    }

    @Override
    public boolean isSelectable(String value) {
        return true;
    }

    @Nullable
    @Override
    public Icon getIconFor(String aValue) {
        return null;
    }

    @NotNull
    @Override
    public String getTextFor(String value) {
        return value;
    }

    @Nullable
    @Override
    public ListSeparator getSeparatorAbove(String value) {
        return null;
    }

    @Override
    public int getDefaultOptionIndex() {
        return 0;
    }


    @Nullable
    @Override
    public String getTitle() {
        return "Template Type";
    }

    @Nullable
    @Override
    public PopupStep onChosen(String selectedValue, boolean finalChoice) {
        _selectedType = selectedValue;
        return FINAL_CHOICE;
    }

    @Override
    public boolean hasSubstep(String selectedValue) {
        return true;
    }

    @Override
    public void canceled() {

    }

    @Override
    public boolean isMnemonicsNavigationEnabled() {
        return false;
    }

    @Nullable
    @Override
    public MnemonicNavigationFilter<String> getMnemonicNavigationFilter() {
        return null;
    }

    @Override
    public boolean isSpeedSearchEnabled() {
        return false;
    }

    @Nullable
    @Override
    public SpeedSearchFilter<String> getSpeedSearchFilter() {
        return null;
    }

    @Override
    public boolean isAutoSelectionEnabled() {
        return false;
    }

    @Nullable
    @Override
    public Runnable getFinalRunnable() {

        if(_selectedType == null) {
            return null;
        }

        return new NamePopup(_project, _selectedType, _directory);
    }
}

public class AddCode extends AnAction
{
    public AddCode()
    {
        super("AddCode");
    }

    public void actionPerformed(AnActionEvent event)
    {
        Navigatable nav = event.getData(CommonDataKeys.NAVIGATABLE);
        if (nav != null && nav instanceof PsiDirectory)
        {
            PsiDirectory dir = (PsiDirectory)nav;
            String path = dir.getVirtualFile().getCanonicalPath();
            Project proj = event.getProject();

            ListPopup listPopup = JBPopupFactory.getInstance().createListPopup(new TemplateList(proj, path));
            listPopup.showCenteredInCurrentWindow(event.getProject());
        }
    }
}
