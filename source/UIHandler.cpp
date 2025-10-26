#include "../headers/UIHandler.h"

#include <../libraries/glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


namespace UserInterface
{
        UIHandler* UIHandler::instance = nullptr;



        UIHandler::UIHandler() 
        {
            getInstance();
            window = glfwCreateWindow(800, 600, "Janelinha", NULL, NULL);
            
        }
        UIHandler::~UIHandler()
        {
        }
            
        void UIHandler::InitializeLibraries()
        {
            // Setup Dear ImGui context
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
            ImGui::StyleColorsDark();

            // Setup Platform/Renderer backends
            ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
            ImGui_ImplOpenGL3_Init();

        }
        void UIHandler::run()
        {
            InitializeLibraries();
            if (!window) {
            std::cerr << "Erro: Janela GLFW não foi criada!" << std::endl;
            system("pause"); // Windows: mantém terminal aberto para ver a mensagem
            return;
        }
            ImGui::Begin("TMSIM");

            while (!glfwWindowShouldClose(window)) 
            {
                // Processar eventos
                glfwPollEvents();

                // Iniciar novo frame ImGui
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();


                ImGui::ShowDemoWindow();

                // Renderização
                ImGui::Render();
                
                int display_w, display_h;
                glfwGetFramebufferSize(window, &display_w, &display_h);
                glViewport(0, 0, display_w, display_h);
                glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                // Renderizar dados do ImGui
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

                glfwSwapBuffers(window);
            }

            end();
            std::cout << "Programa finalizado. Pressione Enter para sair." << std::endl;
            std::cin.get(); // Faz o terminal esperar entrada do usuário
        }

        void UIHandler::end()
        {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();

            glfwDestroyWindow(window);
            glfwTerminate();
        }
}