#include "DirectZob.h"
#include "Events.h"
#include "tinyxml.h"

static char buffer[MAX_PATH];

DirectZob *DirectZob::singleton = nullptr;

DirectZob::DirectZob()
{
	DirectZob::singleton= this; 
}

DirectZob::~DirectZob()
{

}

std::string DirectZob::ExePath() {

	return std::string("D:\\_PERSO\\directZob\\directZob\\resources\\");
	return std::string("C:\\_GIT\\directZob\\x64\\DLL Debug");

	char b[MAX_PATH];
	GetModuleFileName(NULL, b, MAX_PATH);
	std::string::size_type pos = std::string(b).find_last_of("\\/");
	return std::string(b).substr(0, pos);
}

void DirectZob::LoadScene(std::string& file)
{
	TiXmlDocument doc("Scene");
	doc.LoadFile(file.c_str());
	//doc.
	//doc.Parse(demoStart);

	TiXmlElement* root = doc.FirstChildElement("Scene");
	TiXmlElement* fe = root->FirstChildElement("Texture");
	for (TiXmlElement* e = root->FirstChildElement("Texture"); e != NULL; e = e->NextSiblingElement("Texture"))
	{
		std::string name = e->Attribute("name");
		std::string path = e->Attribute("file");
		m_textureManager->LoadTexture(name, path);
	}
	for (TiXmlElement* e = root->FirstChildElement("Camera"); e != NULL; e = e->NextSiblingElement("Camera"))
	{
		std::string name = e->Attribute("name");
		Vector3 p;
		Vector3 t;
		Vector3 u;
		float fov = 0.0f;
		m_cameraManager->LoadCamera(name, p, t, u, fov);
	}
	if (doc.Error())
	{
		printf("Error in %s: %s\n", doc.Value(), doc.ErrorDesc());
	}
}


void DirectZob::Init()
{
	m_events = new Events();
	m_events->AddEvent(0, "Init engine");
	m_engine = new Engine(WIDTH, HEIGHT, m_events);
	m_textureManager = new TextureManager();
	m_events->AddEvent(0, " OK\n");
	int dx = 1;
	int dy = 1;
	float r = 0.0f;
	long frame = 0;
	float rot = 0.0;
	char frameCharBuffer[sizeof(ulong)];

	Matrix2x2 m;
	int state;
	Mesh* mesh = NULL;
	Mesh* mesh2 = NULL;
	Mesh* mesh3 = NULL;
	Mesh* mesh4 = NULL;
	Mesh* mesh5 = NULL;
	Mesh* mesh6 = NULL;
	
	std::string path = ExePath();

	std::string file;
	file = path + "cottage_diffuse_256.png";
	Texture* texCottage = new Texture(file.c_str(), "0", m_events);


	file = path + "earth_256.png";
	Texture* texEarth = new Texture(file.c_str(), "a", m_events);
	file = path + "font2.png";
	Texture* fontTex = new Texture(file.c_str(), "b", m_events);

	file = path + "cottage_obj.obj";
	mesh = new Mesh(file.c_str(), texCottage, m_events);
	file = path + "camaro.obj";
	mesh2 = new Mesh(file.c_str(), texCottage, m_events);
	file = path + "man.obj";
	mesh3 = new Mesh(file.c_str(), texCottage, m_events);
	file = path + "sphere.obj";
	mesh4 = new Mesh(file.c_str(), texEarth, m_events);

	file = path + "beach2.png";
	Texture* texBeach = new Texture(file.c_str(), "c", m_events);
	file = path + "beach2.obj";
	mesh5 = new Mesh(file.c_str(), texBeach, m_events);

	file = path + "water.png";
	Texture* texWater = new Texture(file.c_str(), "d", m_events);
	file = path + "water.obj";
	mesh6 = new Mesh(file.c_str(), texWater, m_events);

	//m_engine->Add(mesh);
	//m_engine->Add(mesh2);
	//m_engine->Add(mesh3);
	//m_engine->Add(mesh4);
	m_engine->Add(mesh5);
	m_engine->Add(mesh6);

	m_text = new Text2D(m_engine, fontTex, 32, 8, m_events);


	static Vector3 camRot = Vector3(0, 0, 0);
	static Vector3 camPos = Vector3(0, -12.40f, -50);
	static Vector3 camTarget = Vector3(0, 0.1f, 1.0f);
	static Vector3 up = Vector3(0, 1.0f, 0);
	m_FPSCam = new Camera("FPS cam", Vector3(0, -2.40f, -50), Vector3(0, -2.40f, -49), Vector3(0, 1.0f, 0), 45.0f, m_engine->GetBufferData());
	m_freeCam = new Camera("Free cam", Vector3(0.0f, -50.0f, -50.0f), Vector3(0, 0, 0), Vector3(0, 1.0f, 0), 45.0f, m_engine->GetBufferData());

	m_curCam = m_freeCam;

	m_engine->Start();
}

static float rot = 0.0f;

int DirectZob::RunAFrame()
{
	int state=0;
	//for (;;)
	{
		//m_engine->ClearBuffer(&Color(255,63,149,255));
		m_engine->ClearBuffer(&Color::White);

		m_freeCam->Update();
		m_FPSCam->Update();

		//if (g_bShowGrid)
		{
			//m_engine->DrawGrid(m_curCam);
		}
		static float tx = 0;
		static float ty = 0;
		static float tz = 0;
		static float scale = 0.25f;// 1.0f / 15.0f;// 0.5f;

		std::vector<Mesh*>* meshes = m_engine->GetMeshVector();
		for (int i = 0; i < meshes->size(); i++)
		{
			meshes->at(i)->Init();
			meshes->at(i)->SetRotation(0,rot,0);
		}
		rot += 1.0f;
		/*if (g_bShowMeshes)
		{
			if (mesh)
			{
				mesh->Init();
				mesh->SetTranslation(0, 0, -10);
				mesh->SetSCale(scale, scale, scale);
				mesh->SetRotation(0, rot, 0);
				//mesh->Draw(m_curCam, m_engine);
			}
			if (mesh2)
			{
				mesh2->Init();
				mesh2->SetTranslation(0, 0, 0);
				mesh2->SetSCale(scale, scale, scale);
				mesh2->SetRotation(0, rot + 10, 0);
				//mesh2->Draw(m_curCam, m_engine);
			}
			if (mesh3)
			{
				mesh3->Init();
				mesh3->SetTranslation(-5, -1, -1);
				mesh3->SetSCale(scale, scale, scale);
				mesh3->SetRotation(rot - 10, rot + 20, rot);
				//mesh3->Draw(m_curCam, m_engine);
			}
			if (mesh4)
			{
				mesh4->Init();
				mesh4->SetTranslation(5, 5, -2);
				mesh4->SetSCale(scale, scale, scale);
				mesh4->SetRotation(rot, rot + 30, rot);
				//mesh4->Draw(m_curCam, m_engine);
			}
			if (mesh5)
			{
				mesh5->Init();
				//mesh5->SetTranslation(5, 5, -2);
				mesh5->SetSCale(1, 1, 1);
				//mesh5->SetRotation(rot, rot + 30, rot);
				mesh5->SetRotation(0, 90, 0);
				//mesh5->Draw(m_curCam, m_engine);
			}
			if (mesh6)
			{
				mesh6->Init();
				//mesh5->SetTranslation(5, 5, -2);
				mesh6->SetSCale(1, 1, 1);
				//mesh5->SetRotation(rot, rot + 30, rot);
				mesh6->SetRotation(0, 90, 0);
				//mesh5->Draw(m_curCam, m_engine);
			}
		}*/

		state = m_engine->Update(m_curCam);

		snprintf(buffer, MAX_PATH, "Triangles : %lu / %lu", m_engine->GetNbDrawnTriangles(), m_engine->GetNbTriangles());
		m_text->Print(0, 0, 1, &std::string(buffer), 0xFFFFFFFF);

		const Vector3* cp = m_curCam->GetPosition();
		const Vector3* ct = m_curCam->GetTarget();
		const Vector3* cf = m_curCam->GetForward();
		snprintf(buffer, MAX_PATH, "Cam %s pos :  %.2f, %.2f, %.2f, tar : %.2f, %.2f, %.2f, fw : %.2f, %.2f, %.2f",
			m_curCam->GetName(),
			cp->x, cp->y, cp->z,
			ct->x, ct->y, ct->z,
			cf->x, cf->y, cf->z
		);
		m_text->Print(0, 8, 1, &std::string(buffer), 0xFFFFFFFF);

		snprintf(buffer, MAX_PATH, "FPS : %.2f, render : %.2fms, geom : %.2f", m_engine->GetFps(), m_engine->GetRenderTime(), m_engine->GetGeometryTime());
		float t = m_engine->GetFps();
		t = (1.0f / t) * 1000.0f;
		if (t < TARGET_MS_PER_FRAME)
		{
			m_text->Print(0, 16, 1, &std::string(buffer), 0xFF00FF00);
			Sleep(TARGET_MS_PER_FRAME - t);
		}
		else
		{
			m_text->Print(0, 16, 1, &std::string(buffer), 0xFFFF0000);
		}
	}
	return state;
}